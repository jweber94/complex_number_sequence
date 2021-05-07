#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <yaml-cpp/yaml.h>

#include "complex.hpp"
#include "mandelbrot_utils.cpp"

int main() {

  // parse the config for the run
  std::string config_path;
  std::cout << "Please insert the input path\n";
  std::cin >> config_path;
  std::cout << "\n";
  YAML::Node config_reader = YAML::LoadFile(config_path);

  run_config config_vars;
  std::ofstream resultStream;

  load_run_configuration(config_reader, config_vars);

  std::cout << "Calculation started, please wait!\n";
  calculate_convergence_radius(resultStream, config_vars);
  std::cout << "Calculation finished. Saved result in "
       << config_reader["nameResult"].as<std::string>() << "\n";

  return 0;
}
