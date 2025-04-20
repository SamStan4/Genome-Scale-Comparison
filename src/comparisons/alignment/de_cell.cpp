#include "./dp_cell.hpp"

// MARK: private methods

void dp_cell::score_s(
  const dp_cell& cell_s,
  const char c_one,
  const char c_two,
  const int64_t match_score,
  const int64_t mismatch_score
) {
  const int64_t s_candidate = cell_s.get_s_score();
  const int64_t d_candidate = cell_s.get_d_score();
  const int64_t i_candidate = cell_s.get_i_score();
  const int64_t max_candidate = std::max(s_candidate, std::max(d_candidate, i_candidate));
  if (s_candidate == max_candidate) {
    this->m_s_matches = cell_s.get_s_matches();
  } else if (d_candidate == max_candidate) {
    this->m_s_matches = cell_s.get_d_matches();
  } else {
    this->m_s_matches = cell_s.get_i_matches();
  }
  this->m_s_matches += (c_one == c_two ? 1 : 0);
  this->m_s_score = std::max(dp_cell::min_score, max_candidate + (c_one == c_two ? match_score : mismatch_score));
}

void dp_cell::score_d(
  const dp_cell& cell_d,
  const int64_t opening_gap_score,
  const int64_t gap_extension_score
) {
  const int64_t s_candidate = cell_d.get_s_score() + opening_gap_score + gap_extension_score;
  const int64_t d_candidate = cell_d.get_d_score() + gap_extension_score;
  const int64_t i_candidate = cell_d.get_i_score() + opening_gap_score + gap_extension_score;
  const int64_t max_candidate = std::max(s_candidate, std::max(d_candidate, i_candidate));
  if (s_candidate == max_candidate) {
    this->m_d_matches = cell_d.get_s_matches();
  } else if (d_candidate == max_candidate) {
    this->m_d_matches = cell_d.get_d_matches();
  } else {
    this->m_d_matches = cell_d.get_i_matches();
  }
  this->m_d_score = std::max(dp_cell::min_score, max_candidate);
}

void dp_cell::score_i(
  const dp_cell& cell_i,
  const int64_t opening_gap_score,
  const int64_t gap_extension_score
) {
  const int64_t s_candidate = cell_i.get_s_score() + opening_gap_score + gap_extension_score;
  const int64_t d_candidate = cell_i.get_d_score() + opening_gap_score + gap_extension_score;
  const int64_t i_candidate = cell_i.get_i_score() + gap_extension_score;
  const int64_t max_candidate = std::max(s_candidate, std::max(d_candidate, i_candidate));
  if (s_candidate == max_candidate) {
    this->m_i_matches = cell_i.get_s_matches();
  } else if (d_candidate == max_candidate) {
    this->m_i_matches = cell_i.get_d_matches();
  } else {
    this->m_i_matches = cell_i.get_i_matches();
  }
  this->m_i_score = std::max(dp_cell::min_score, max_candidate);
}

// MARK: public methods

dp_cell::dp_cell() :
  m_s_score(0),
  m_d_score(0),
  m_i_score(0),
  m_s_matches(0),
  m_d_matches(0),
  m_i_matches(0) {
}

dp_cell::~dp_cell() {
}

int64_t dp_cell::get_max_score(void) const {
  return std::max(this->m_s_score, std::max(this->m_d_score, this->m_i_score));
}

int32_t dp_cell::get_max_score_matches(void) const {
  const int64_t max_score = std::max(this->m_s_score, std::max(this->m_d_score, this->m_i_score));
  if (max_score == this->m_s_score) {
    return this->m_s_matches;
  } else if (max_score == this->m_d_score) {
    return this->m_d_matches;
  }
  return this->m_i_matches;
}

void dp_cell::score_cell(
  const dp_cell& cell_s,
  const dp_cell& cell_d,
  const dp_cell& cell_i,
  const char c_one,
  const char c_two,
  const int64_t match_score,
  const int64_t mismatch_score,
  const int64_t opening_gap_score,
  const int64_t gap_extension_score
) {
  this->score_s(cell_s, c_one, c_two, match_score, mismatch_score);
  this->score_d(cell_d, opening_gap_score, gap_extension_score);
  this->score_i(cell_i, opening_gap_score, gap_extension_score);
}

void dp_cell::reset_cell(void) {
  this->m_s_score = 0;
  this->m_d_score = 0;
  this->m_i_score = 0;
  this->m_s_matches = 0;
  this->m_d_matches = 0;
  this->m_i_matches = 0;
}

void dp_cell::set_top_row(size_t col_idx, const int64_t opening_gap_score, const int64_t gap_extension_score) {
  this->m_s_score = dp_cell::min_score;
  this->m_d_score = dp_cell::min_score;
  this->m_i_score = opening_gap_score + (static_cast<int64_t>(col_idx) * gap_extension_score);
  this->m_s_matches = 0;
  this->m_d_matches = 0;
  this->m_i_matches = 0;
}

void dp_cell::set_left_col(size_t row_idx, const int64_t opening_gap_score, const int64_t gap_extension_score) {
  this->m_s_score = dp_cell::min_score;
  this->m_d_score = opening_gap_score + (static_cast<int64_t>(row_idx) * gap_extension_score);
  this->m_i_score = dp_cell::min_score;
  this->m_s_matches = 0;
  this->m_d_matches = 0;
  this->m_i_matches = 0;
}

// MARK: getters

int64_t dp_cell::get_s_score(void) const {
  return this->m_s_score;
}

int64_t dp_cell::get_d_score(void) const {
  return this->m_d_score;
}

int64_t dp_cell::get_i_score(void) const {
  return this->m_i_score;
}

int32_t dp_cell::get_s_matches(void) const {
  return this->m_s_matches;
}

int32_t dp_cell::get_d_matches(void) const {
  return this->m_d_matches;
}

int32_t dp_cell::get_i_matches(void) const {
  return this->m_i_matches;
}

// MARK: setters

void dp_cell::set_s_score(int64_t _s_score) {
  this->m_s_score = _s_score;
}

void dp_cell::set_d_score(int64_t _d_score) {
  this->m_d_score = _d_score;
}

void dp_cell::set_i_score(int64_t _i_score) {
  this->m_i_score = _i_score;
}

void dp_cell::set_s_matches(int32_t _s_matches) {
  this->m_s_matches = _s_matches;
}

void dp_cell::set_d_matches(int32_t _d_matches) {
  this->m_d_matches = _d_matches;
}

void dp_cell::set_i_matches(int32_t _i_matches) {
  this->m_i_matches = _i_matches;
}

// MARK: printers

void dp_cell::print_scores(std::ostream& os) const {
  os << "(s-[" << this->m_s_score << "], d-[" << this->m_d_score << "], i-[" << this->m_i_score << "])";
}

void dp_cell::print_matches(std::ostream& os) const {
  os << "(s-" << this->m_s_matches << ", d-" << this->m_d_matches << ", i-" << this->m_i_matches << ")";
}

void dp_cell::print_all(std::ostream& os) const {
  os << "{(s-" << this->m_s_score << ", d-" << this->m_d_score << ", i-" << this->m_i_score << "), (s-"
  << this->m_s_matches << ", d-" << this->m_d_matches << ", i-" << this->m_i_matches << ")}";
}

std::string dp_cell::to_string(void) const {
  std::ostringstream string_stream;
  string_stream
    << "{(s_score-[" << this->m_s_score << "], d_score-[" << this->m_d_score << "], i_score[" << this->m_i_score
    << "]), (s_match-[" << this->m_s_matches << "], d_match[" << this->m_d_matches << "], i_match[" << this->m_d_matches
    << "])}";
  return string_stream.str();
}