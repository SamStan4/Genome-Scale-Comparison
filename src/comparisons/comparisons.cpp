#include "./comparisons.hpp"

void execute_single_comparison(
  const std::string& str_one,
  const std::string& str_two,
  const size_t i,
  const size_t j,
  std::vector<std::vector<size_t>>& result_dest
) {
  std::pair<size_t, std::pair<std::vector<size_t>, std::vector<size_t>>> lrs_info = suffix_tree({str_one, str_two}).get_lrs(0, 1);
  if (lrs_info.second.first.empty() || lrs_info.second.second.empty()) {
    throw std::runtime_error("crash");
  }
  std::string prefix_one = str_one.substr(0, lrs_info.second.first.front());
  std::string prefix_two = str_two.substr(0, lrs_info.second.second.front());
  std::reverse(prefix_one.begin(), prefix_one.end());
  std::reverse(prefix_two.begin(), prefix_two.end());
  const std::string suffix_one = str_one.substr(lrs_info.second.first.front() + lrs_info.first);
  const std::string suffix_two = str_two.substr(lrs_info.second.second.front() + lrs_info.first);
  const size_t result =
    lrs_info.first +
    alignment::execute_modified_global_alignment(prefix_one, prefix_two, 1, -2, -5, -2) +
    alignment::execute_modified_global_alignment(suffix_one, suffix_two, 1, -2, -5, -2);
  result_dest[i][j] = result;
  result_dest[j][i] = result;
  std::cout << "here " << i << " " << j << std::endl;
}

namespace comparisons {
  std::vector<std::vector<size_t>> execute_comparisons(std::vector<std::string>& strings) {
    const size_t strings_size = strings.size();
    std::vector<std::vector<size_t>> results(strings_size, std::vector<size_t>(strings_size, 0));
    std::vector<std::thread> threads;
    for (size_t i = 0; i < strings_size; ++i) {
      for (size_t j = i + 1; j < strings_size; ++j) {
        // threads.emplace_back(
        //   execute_single_comparison,
        //   strings[i],
        //   strings[j],
        //   i,
        //   j,
        //   std::ref(results)
        // );
        execute_single_comparison(strings[i], strings[j], i, j, results);
      }
    }
    for (size_t i = 0; i < threads.size(); ++i) {
      threads[i].join();
    }
    return results;
  }
}