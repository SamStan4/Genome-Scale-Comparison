#ifndef __COMPARISONS_HPP__
#define __COMPARISONS_HPP__

#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include "./alignment/alignment.hpp"
#include "./suffix_tree/suffix_tree.hpp"

void execute_single_comparison(
  const std::string&,
  const std::string&,
  const size_t,
  const size_t,
  std::vector<std::vector<size_t>>&
);

namespace comparisons {
  std::vector<std::vector<size_t>> execute_comparisons(std::vector<std::string>&);
}

#endif