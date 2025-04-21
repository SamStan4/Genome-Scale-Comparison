#ifndef __COMPARISONS_HPP__
#define __COMPARISONS_HPP__

#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include <chrono>
#include "./alignment/alignment.hpp"
#include "./suffix_tree/suffix_tree.hpp"

// for progress logs
#define DEV_BUILD 1
#define USE_MC_SUFFIX_TREE 0

std::pair<std::chrono::duration<double>, std::chrono::duration<double>> execute_single_comparison(
  const std::string&,
  const std::string&,
  const size_t,
  const size_t,
  std::vector<std::vector<size_t>>&,
  const int64_t,
  const int64_t,
  const int64_t,
  const int64_t
);

#if !USE_MC_SUFFIX_TREE
  std::pair<size_t, std::pair<std::vector<size_t>, std::vector<size_t>>> longest_common_substring(
    const std::string &s1,
    const std::string &s2
  );
#endif

namespace comparisons {
  std::vector<std::vector<size_t>> execute_comparisons(
    std::vector<std::string>&,
    const int64_t,
    const int64_t,
    const int64_t,
    const int64_t,
    std::chrono::duration<double>&,
    std::chrono::duration<double>&
  );
}

#endif