#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <yaml-cpp/yaml.h>

#include "complex.hpp"
#include "mandelbrot_utils.cpp"

int main() {

  using namespace std;

  // parse the config for the run
  std::string config_path;
  std::cout << "Please insert the input path\n";
  std::cin >> config_path;
  std::cout << "\n";

  YAML::Node config_reader = YAML::LoadFile(config_path);

  run_config config_vars;
  ofstream resultStream;

  load_run_configuration(config_reader, config_vars);

  cout << "Calculation started, please wait!\n";
  calculate_convergence_radius(resultStream, config_vars);
  cout << "Calculation finished. Saved result in "
       << config_reader["nameResult"].as<string>() << "\n";

  return 0;
}
