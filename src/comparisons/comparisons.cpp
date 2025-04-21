#include "./comparisons.hpp"

// for testing, not used in actual submitted output
#if !USE_MC_SUFFIX_TREE
  std::pair<size_t, std::pair<std::vector<size_t>, std::vector<size_t>>> longest_common_substring(const std::string &s1, const std::string &s2) {
    size_t n = s1.size();
    size_t m = s2.size();
    size_t maxLength = 0;

    std::vector<std::vector<size_t>> dp(n + 1, std::vector<size_t>(m + 1, 0));
    std::vector<std::pair<size_t, size_t>> endPositions;

    for (size_t i = 1; i <= n; ++i) {
      for (size_t j = 1; j <= m; ++j) {
        if (s1[i - 1] == s2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
          if (dp[i][j] > maxLength) {
            maxLength = dp[i][j];
            endPositions.clear();
            endPositions.emplace_back(i - 1, j - 1);
          } else if (dp[i][j] == maxLength) {
            endPositions.emplace_back(i - 1, j - 1);
          }
        }
      }
    }

    std::vector<size_t> startsInS1, startsInS2;
    for (const auto& pos : endPositions) {
      startsInS1.push_back(pos.first - maxLength + 1);
      startsInS2.push_back(pos.second - maxLength + 1);
    }

    return {maxLength, {startsInS1, startsInS2}};
  }
#endif

std::pair<std::chrono::duration<double>, std::chrono::duration<double>> execute_single_comparison(
  const std::string& str_one,
  const std::string& str_two,
  const size_t i,
  const size_t j,
  std::vector<std::vector<size_t>>& result_dest,
  const int64_t match_score,
  const int64_t mismatch_score,
  const int64_t opening_gap_score,
  const int64_t gap_extension_score
) {
  if (i == j) {
    result_dest[i][j] = str_one.size();
    #if DEV_BUILD
      std::cout << "completed: " << "(" << i << ", " << j << ") tree-time: " << 0 << " alignment-time: " << 0 << std::endl;
    #endif
    return {std::chrono::duration<double>::zero(), std::chrono::duration<double>::zero()};
  }
  const auto tree_start = std::chrono::high_resolution_clock::now();
  #if USE_MC_SUFFIX_TREE
    std::pair<size_t, std::pair<std::vector<size_t>, std::vector<size_t>>> lrs_info = suffix_tree({str_one, str_two}).get_lrs(0, 1);
  #else
    std::pair<size_t, std::pair<std::vector<size_t>, std::vector<size_t>>> lrs_info = longest_common_substring(str_one, str_two);
  #endif
  const auto tree_end = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<double> tree_elapsed = tree_end - tree_start;
  if (lrs_info.second.first.empty() || lrs_info.second.second.empty()) {
    throw std::runtime_error("crash");
  }
  std::string prefix_one = str_one.substr(0, lrs_info.second.first.front());
  std::string prefix_two = str_two.substr(0, lrs_info.second.second.front());
  std::reverse(prefix_one.begin(), prefix_one.end());
  std::reverse(prefix_two.begin(), prefix_two.end());
  const std::string suffix_one = str_one.substr(lrs_info.second.first.front() + lrs_info.first);
  const std::string suffix_two = str_two.substr(lrs_info.second.second.front() + lrs_info.first);
  const auto alignment_start = std::chrono::high_resolution_clock::now();
  const size_t result =
    lrs_info.first +
    alignment::execute_modified_global_alignment(
      prefix_one,
      prefix_two,
      match_score,
      mismatch_score,
      opening_gap_score,
      gap_extension_score
    ) +
    alignment::execute_modified_global_alignment(
      suffix_one,
      suffix_two,
      match_score,
      mismatch_score,
      opening_gap_score,
      gap_extension_score
    );
  const auto alignment_end = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<double> alignment_elapsed = alignment_end - alignment_start;
  result_dest[i][j] = result;
  result_dest[j][i] = result;
  #if DEV_BUILD
    std::cout << "completed: " << "(" << i << ", " << j << ") tree-time: " << tree_elapsed.count() << " alignment-time: " << alignment_elapsed.count() << std::endl;
  #endif
  return {tree_elapsed, alignment_elapsed};
}

namespace comparisons {
  std::vector<std::vector<size_t>> execute_comparisons(
    std::vector<std::string>& strings,
    const int64_t match_score,
    const int64_t mismatch_score,
    const int64_t opening_gap_score,
    const int64_t gap_extension_score,
    std::chrono::duration<double>& tree_elapsed_out,
    std::chrono::duration<double>& alignment_elapsed_out
  ) {
    std::chrono::duration<double> tree_elapsed = std::chrono::duration<double>::zero();
    std::chrono::duration<double> alignment_elapsed = std::chrono::duration<double>::zero();
    const size_t strings_size = strings.size();
    std::vector<std::vector<size_t>> results(strings_size, std::vector<size_t>(strings_size, 0));
    for (size_t i = 0; i < strings_size; ++i) {
      for (size_t j = i; j < strings_size; ++j) {
        auto [new_tree_elapsed, new_alignment_elapsed] = execute_single_comparison(
          strings[i],
          strings[j],
          i,
          j,
          results,
          match_score,
          mismatch_score,
          opening_gap_score,
          gap_extension_score
        );
        tree_elapsed += new_tree_elapsed;
        alignment_elapsed += new_alignment_elapsed;
      }
    }
    tree_elapsed_out = tree_elapsed;
    alignment_elapsed_out = alignment_elapsed;
    return results;
  }
}