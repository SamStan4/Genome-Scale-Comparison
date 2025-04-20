#include "./io_utils.hpp"

namespace io_utils {
  bool load_one_gene(
    const char* file_path,
    std::string& out_string,
    std::string& out_string_name
  ) {
    out_string.clear();
    out_string_name.clear();
    bool first_string_flag = true;
    std::ifstream input_stream(file_path);
    if (!input_stream.is_open()) {
      return false;
    }
    std::string buffer;
    while (std::getline(input_stream, buffer)) {
      if (!buffer.empty() && buffer.back() == '\r') {
        buffer.pop_back();
      }
      if (buffer.empty()) {
        continue;
      } else if (buffer[0] == '>') {
        if (first_string_flag) {
          first_string_flag = false;
          out_string_name = buffer.substr(1);
        } else {
          return true;
        }
        continue;
      }
      out_string += buffer;
    }
    input_stream.close();
    return true;
  }

  bool load_one_gene(const char* file_path, std::string& out_string) {
    out_string.clear();
    bool first_string_flag = true;
    std::ifstream input_stream(file_path);
    if (!input_stream.is_open()) {
      return false;
    }
    std::string buffer;
    while (std::getline(input_stream, buffer)) {
      if (!buffer.empty() && buffer.back() == '\r') {
        buffer.pop_back();
      }
      if (buffer.empty()) {
        continue;
      } else if (buffer[0] == '>') {
        if (first_string_flag) {
          first_string_flag = false;
        } else {
          return true;
        }
        continue;
      }
      out_string += buffer;
    }
    input_stream.close();
    return true;
  }

  bool load_alphabet(const char* file_path, std::string& out_string) {
    out_string.clear();
    std::ifstream input_stream(file_path);
    if (!input_stream.is_open()) {
      return false;
    }
    std::string buffer;
    std::unordered_set<char> alphabet_set;
    while (std::getline(input_stream, buffer)) {
      if (!buffer.empty() && buffer.back() == '\r') {
        buffer.pop_back();
      }
      for (const char c : buffer) {
        if (std::isupper(c)) {
          alphabet_set.insert(c);
        }
      }
    }
    input_stream.close();
    out_string.reserve(alphabet_set.size());
    for (const char c : alphabet_set) {
      out_string.push_back(c);
    }
    std::sort(out_string.begin(), out_string.end());
    return true;
  }

  bool load_alignment_params(
    const char* file_path,
    int64_t& out_match_score,
    int64_t& out_mismatch_score,
    int64_t& out_opening_gap_score,
    int64_t& out_gap_extension_score
  ) {
    std::ifstream input_stream(file_path);
    if (!input_stream.is_open()) {
      return false;
    }
    std::unordered_map<std::string, int64_t> param_map = {
      {"match", 0},
      {"mismatch", 0},
      {"g", 0},
      {"h", 0}
    };
    std::string buffer;
    int8_t total_params = 0;
    while (std::getline(input_stream, buffer)) {
      if (buffer.empty()) {
        continue;
      }
      try {
        std::stringstream read_stream(buffer);
        std::string key;
        std::string val;
        read_stream >> key >> val;
        if (param_map.find(key) != param_map.end()) {
          param_map[key] = static_cast<int64_t>(std::stoi(val));
          ++total_params;
        }
      } catch (...) {
        continue;
      }
    }
    input_stream.close();
    out_match_score = param_map["match"];
    out_mismatch_score = param_map["mismatch"];
    out_opening_gap_score = param_map["h"];
    out_gap_extension_score = param_map["g"];
    return total_params == 4;
  }
}