#ifndef __DP_CELL_HPP__
#define __DP_CELL_HPP__

#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>

class dp_cell {
private:
  static constexpr int64_t min_score = static_cast<int64_t>(std::numeric_limits<int32_t>::min());

  int64_t m_s_score;
  int64_t m_d_score;
  int64_t m_i_score;

  int32_t m_s_matches;
  int32_t m_d_matches;
  int32_t m_i_matches;

  void score_s(
    const dp_cell&,
    const char,
    const char,
    const int64_t,
    const int64_t
  );
  void score_d(
    const dp_cell&,
    const int64_t,
    const int64_t
  );
  void score_i(
    const dp_cell&,
    const int64_t,
    const int64_t
  );
public:
  dp_cell();
  ~dp_cell();

  int64_t get_max_score(void) const;
  int32_t get_max_score_matches(void) const;
  void score_cell(
    const dp_cell&,
    const dp_cell&,
    const dp_cell&,
    const char,
    const char,
    const int64_t,
    const int64_t,
    const int64_t,
    const int64_t
  );
  void reset_cell(void);

  void set_top_row(size_t col_idx, const int64_t, const int64_t);
  void set_left_col(size_t row_idx, const int64_t, const int64_t);

  int64_t get_s_score(void) const;
  int64_t get_d_score(void) const;
  int64_t get_i_score(void) const;

  int32_t get_s_matches(void) const;
  int32_t get_d_matches(void) const;
  int32_t get_i_matches(void) const;

  void set_s_score(int64_t _s_score);
  void set_d_score(int64_t _d_score);
  void set_i_score(int64_t _i_score);

  void set_s_matches(int32_t _s_matches);
  void set_d_matches(int32_t _d_matches);
  void set_i_matches(int32_t _i_matches);

  void print_scores(std::ostream&) const;
  void print_matches(std::ostream&) const;
  void print_all(std::ostream&) const;

  std::string to_string(void) const;
};

#endif