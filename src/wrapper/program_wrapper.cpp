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
  auto result = comparisons::execute_comparisons(gene_strings);
  std::ofstream resutl_stream("./output.csv");
  for (size_t i = 0; i < result.size(); ++i) {
    for (size_t j = 0; j < result[i].size(); ++j) {
      resutl_stream << result[i][j] << ",";
    }
    resutl_stream << std::endl;
  }
  resutl_stream.close();
}