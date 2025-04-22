#include <iostream>
#include "./wrapper/program_wrapper.hpp"

int main(int argc, char** argv) {
  program_wrapper& app = program_wrapper::get_instance();
  app.run_program_lcs(argc, argv);
  // app.run_program(argc, argv);
  // app.run_program_time(argc, argv);
  return 0;
}