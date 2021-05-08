#include <fstream>
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

#include "complex.hpp"
#include "mandelbrot_utils.cpp"

int main() {

  // parse the config for the run
  std::string config_path;
  std::cout << "Please insert the input path\n";
  //std::cin >> config_path;
  //std::cout << "\n";
  config_path = "../etc/mandelbrot_config_case_1A.yml"; // debug 
  /*
  YAML::Node config_reader = YAML::LoadFile(config_path);

  run_config config_vars{};
  std::ofstream resultStream;

  load_run_configuration(config_reader, config_vars);

  std::cout << "Calculation started, please wait!\n";
  calculate_convergence_radius(resultStream, config_vars);
  std::cout << "Calculation finished. Saved result in "
       << config_reader["nameResult"].as<std::string>() << "\n";
  */

 std::cout << "Finished with the calculation of the given complex number series\n"; 

  return 0;
}
