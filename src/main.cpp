#include "calculation_runner.hpp"
#include "config_reader.hpp"
#include <iostream>

int main() {

  // parse the config for the run
  std::string config_path;
  std::cout << "Please insert the input path\n";
  std::cin >> config_path;

  try {
    calculation_utils::ConfigurationLoader config_loader(config_path);
    calculation_utils::CalculationRunner calc_runner(config_loader);

    calc_runner.run_calculation();

    std::cout << "Finished calculation with the configuration from path:\n"
              << config_loader << "\nwith the following configuration:\n"
              << calc_runner << "\n";
  } catch (const std::exception &e) {
    std::cerr << "ERROR: Something went wrong. Please check the config file "
                 "and/or inform the maintainer.\nError-Code: "
              << e.what() << "\n";
  } catch (...) {
    std::cerr
        << "An unknown exeption was thrown. Please inform the maintainer.\n";
  }

  return 0;
}