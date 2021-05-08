#include "mandelbrot_utils.cpp"
#include <iostream>

int main() {

  // parse the config for the run
  std::string config_path;
  std::cout << "Please insert the input path\n";
  std::cin >> config_path;
  std::cout << "\n";

  calculation_utils::ConfigurationLoader config_loader(config_path);
  calculation_utils::CalculationRunner calc_runner(config_loader);

  calc_runner.run_calculation();

  std::cout
      << "Finished with the calculation of the given complex number series\n";
  return 0;
}
