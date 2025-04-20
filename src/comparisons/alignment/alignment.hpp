#ifndef __ALIGNMENT_HPP__
#define __ALIGNMENT_HPP__

#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "./dp_cell.hpp"

namespace alignment {
  int64_t execute_global_alignment(
    const std::string&,
    const std::string&,
    const int64_t,
    const int64_t,
    const int64_t,
    const int64_t
  );

  int32_t execute_modified_global_alignment(
    const std::string&,
    const std::string&,
    const int64_t,
    const int64_t,
    const int64_t, 
    const int64_t
  );
}

#endif