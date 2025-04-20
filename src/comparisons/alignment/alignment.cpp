#include "./alignment.hpp"

namespace alignment {
  // MARK: standard alignment
  int64_t execute_global_alignment(
    const std::string& string_one,
    const std::string& string_two,
    const int64_t match_score,
    const int64_t mismatch_score,
    const int64_t opening_gap_score,
    const int64_t gap_extension_score
  ) {
    const size_t row_size = string_one.size() + 1;
    const size_t col_size = string_two.size() + 1;
    std::vector<dp_cell> cur_dp_row(col_size, dp_cell());
    std::vector<dp_cell> prev_dp_row(col_size, dp_cell());

    for (size_t i = 1; i < col_size; ++i) {
      prev_dp_row[i].set_top_row(i, opening_gap_score, gap_extension_score);
    }

    for (size_t row_idx = 1; row_idx < row_size; ++row_idx) {
      cur_dp_row[0].set_left_col(row_idx, opening_gap_score, gap_extension_score);
      for (size_t col_idx = 1; col_idx < col_size; ++col_idx) {
        cur_dp_row[col_idx].score_cell(
          prev_dp_row[col_idx-1],
          prev_dp_row[col_idx],
          cur_dp_row[col_idx-1],
          string_one[row_idx-1],
          string_two[col_idx-1],
          match_score,
          mismatch_score,
          opening_gap_score,
          gap_extension_score
        );
      }
      std::swap(prev_dp_row, cur_dp_row);
    }
    return prev_dp_row.back().get_max_score();
  }

  int32_t execute_modified_global_alignment(
    const std::string& string_one,
    const std::string& string_two,
    const int64_t match_score,
    const int64_t mismatch_score,
    const int64_t opening_gap_score,
    const int64_t gap_extension_score
  ) {
    const size_t row_size = string_one.size() + 1;
    const size_t col_size = string_two.size() + 1;
    std::vector<dp_cell> cur_dp_row(col_size, dp_cell());
    std::vector<dp_cell> prev_dp_row(col_size, dp_cell());

    for (size_t i = 1; i < col_size; ++i) {
      prev_dp_row[i].set_top_row(i, opening_gap_score, gap_extension_score);
    }

    int64_t max_score = 0;
    int32_t max_score_matches = 0;

    for (size_t row_idx = 1; row_idx < row_size; ++row_idx) {
      cur_dp_row[0].set_left_col(row_idx, opening_gap_score, gap_extension_score);
      for (size_t col_idx = 1; col_idx < col_size; ++col_idx) {
        cur_dp_row[col_idx].score_cell(
          prev_dp_row[col_idx-1],
          prev_dp_row[col_idx],
          cur_dp_row[col_idx-1],
          string_one[row_idx-1],
          string_two[col_idx-1],
          match_score,
          mismatch_score,
          opening_gap_score,
          gap_extension_score
        );
        const int64_t temp_max_score = cur_dp_row[col_idx].get_max_score();

        if (temp_max_score > max_score) {
          max_score = temp_max_score;
          max_score_matches = cur_dp_row[col_idx].get_max_score_matches();
        }
      }
      std::swap(prev_dp_row, cur_dp_row);
    }

    return max_score_matches;
  }
}