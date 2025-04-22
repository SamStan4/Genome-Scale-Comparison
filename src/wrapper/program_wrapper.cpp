#include "./program_wrapper.hpp"

program_wrapper& program_wrapper::get_instance(void) {
    static program_wrapper instance;
    return instance;
}

void program_wrapper::run_program(const int arg_count, const char* const* arg_vector) {
  if (arg_count < 4) {
    std::cerr << "less than 4 args" << std::endl;
    return;
  }
  int64_t match_score = 0;
  int64_t mismatch_score = 0;
  int64_t opening_gap_score = 0;
  int64_t gap_extension_score = 0;
  if (!io_utils::load_alignment_params(arg_vector[1], match_score, mismatch_score, opening_gap_score, gap_extension_score)) {
    throw std::runtime_error("error, couldnt load alignment parameters");
  }
  std::vector<std::string> gene_strings;
  std::vector<std::string> gene_names;
  gene_strings.reserve(arg_count - 2);
  gene_names.reserve(arg_count - 2);
  for (size_t i = 2; i < static_cast<size_t>(arg_count); ++i) {
    std::string cur_gene_string;
    gene_names.push_back(arg_vector[i]);
    if (!io_utils::load_one_gene(arg_vector[i], cur_gene_string)) {
      throw std::runtime_error("error, couldnt load gene string");
    }
    gene_strings.push_back(cur_gene_string);
  }
  std::chrono::duration<double> tree_elapsed;
  std::chrono::duration<double> alignment_elapsed;
  std::vector<std::vector<size_t>> result = comparisons::execute_comparisons(
    gene_strings,
    match_score,
    mismatch_score,
    opening_gap_score,
    gap_extension_score,
    tree_elapsed,
    alignment_elapsed
  );
  std::ofstream result_stream("./output.csv");

  for (size_t i = 2; i < static_cast<size_t>(arg_count); ++i) {
    result_stream << (i - 2) << "," << arg_vector[i] << std::endl;
  }
  result_stream << std::endl << ",";
  for (size_t i = 2; i < static_cast<size_t>(arg_count); ++i) {
    result_stream << (i -2) << ",";
  }
  result_stream << std::endl;
  for (size_t i = 0; i < result.size(); ++i) {
    result_stream << i << ",";
    for (size_t j = 0; j < result[i].size(); ++j) {
      result_stream << result[i][j] << ",";
    }
    result_stream << std::endl;
  }
  result_stream << std::endl;
  result_stream << "tree time," << tree_elapsed.count() << " sec," << std::endl << "alignment time," << alignment_elapsed.count() << " sec," << std::endl;
  result_stream.close();
}

void program_wrapper::run_program_lcs(const int arg_count, const char* const* arg_vector) {
  if (arg_count < 4) {
    std::cerr << "less than 4 args" << std::endl;
    return;
  }
  int64_t match_score = 0;
  int64_t mismatch_score = 0;
  int64_t opening_gap_score = 0;
  int64_t gap_extension_score = 0;
  if (!io_utils::load_alignment_params(arg_vector[1], match_score, mismatch_score, opening_gap_score, gap_extension_score)) {
    throw std::runtime_error("error, couldnt load alignment parameters");
  }
  std::vector<std::string> gene_strings;
  std::vector<std::string> gene_names;
  gene_strings.reserve(arg_count - 2);
  gene_names.reserve(arg_count - 2);
  for (size_t i = 2; i < static_cast<size_t>(arg_count); ++i) {
    std::string cur_gene_string;
    gene_names.push_back(arg_vector[i]);
    if (!io_utils::load_one_gene(arg_vector[i], cur_gene_string)) {
      throw std::runtime_error("error, couldnt load gene string");
    }
    gene_strings.push_back(cur_gene_string);
  }
  std::vector<std::vector<size_t>> result = comparisons::execute_comparisons_lcs(
    gene_strings
  );
  std::ofstream result_stream("./output.csv");
  for (size_t i = 2; i < static_cast<size_t>(arg_count); ++i) {
    result_stream << (i - 2) << "," << arg_vector[i] << std::endl;
  }
  result_stream << std::endl << ",";
  for (size_t i = 2; i < static_cast<size_t>(arg_count); ++i) {
    result_stream << (i -2) << ",";
  }
  result_stream << std::endl;
  for (size_t i = 0; i < result.size(); ++i) {
    result_stream << i << ",";
    for (size_t j = 0; j < result[i].size(); ++j) {
      result_stream << result[i][j] << ",";
    }
    result_stream << std::endl;
  }
  result_stream.close();
}

void program_wrapper::run_program_time(const int arg_count, const char* const* arg_vector) {
  if (arg_count < 4) {
    std::cerr << "less than 4 args" << std::endl;
    return;
  }
  int64_t match_score = 0;
  int64_t mismatch_score = 0;
  int64_t opening_gap_score = 0;
  int64_t gap_extension_score = 0;
  if (!io_utils::load_alignment_params(arg_vector[1], match_score, mismatch_score, opening_gap_score, gap_extension_score)) {
    throw std::runtime_error("error, couldnt load alignment parameters");
  }
  std::vector<std::string> gene_strings;
  std::vector<std::string> gene_names;
  gene_strings.reserve(arg_count - 2);
  gene_names.reserve(arg_count - 2);
  for (size_t i = 2; i < static_cast<size_t>(arg_count); ++i) {
    std::string cur_gene_string;
    gene_names.push_back(arg_vector[i]);
    if (!io_utils::load_one_gene(arg_vector[i], cur_gene_string)) {
      throw std::runtime_error("error, couldnt load gene string");
    }
    gene_strings.push_back(cur_gene_string);
  }
  auto [tree_times, alignment_times] = comparisons::execute_comparisons_times(
    gene_strings,
    match_score,
    mismatch_score,
    opening_gap_score,
    gap_extension_score
  );
  std::ofstream result_stream("./output.csv");
  for (size_t i = 2; i < static_cast<size_t>(arg_count); ++i) {
    result_stream << (i - 2) << "," << arg_vector[i] << std::endl;
  }
  result_stream << std::endl << ",";
  for (size_t i = 2; i < static_cast<size_t>(arg_count); ++i) {
    result_stream << (i -2) << ",";
  }
  result_stream << std::endl;
  for (size_t i = 0; i < tree_times.size(); ++i) {
    result_stream << i << ",";
    for (size_t j = 0; j < tree_times[i].size(); ++j) {
      result_stream << tree_times[i][j].count() << ",";
    }
    result_stream << std::endl;
  }
  result_stream << std::endl;
  result_stream << std::endl << ",";
  for (size_t i = 2; i < static_cast<size_t>(arg_count); ++i) {
    result_stream << (i -2) << ",";
  }
  result_stream << std::endl;
  for (size_t i = 0; i < alignment_times.size(); ++i) {
    result_stream << i << ",";
    for (size_t j = 0; j < alignment_times[i].size(); ++j) {
      result_stream << alignment_times[i][j].count() << ",";
    }
    result_stream << std::endl;
  }
  result_stream << std::endl;
  result_stream.close();
}