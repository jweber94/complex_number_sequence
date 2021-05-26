#include "calculation_runner.hpp"
#include "config_reader.hpp"
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>

int main(int argc, const char *argv[]) {

  // command line parser
  boost::program_options::options_description desc{
      "Options for the complex number series calculation"};
  boost::program_options::variables_map vm;
  std::string config_path = "none";

  try {

    desc.add_options()(
        "help,h", "Help and overview of all possible command line options")(
        "path,p",
        boost::program_options::value<std::string>()->default_value("none"),
        "Path to the configuration file");

    boost::program_options::store(
        boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    config_path = vm["path"].as<std::string>();

    if (vm.count("help")) {
      std::cout << desc << "\n";
      exit(0);
    }
    if ((config_path == "none") || !(boost::filesystem::exists(config_path))) {
      std::cerr << "The path to the config is not valid. Please check your "
                   "config path after --path /path/to/your/config.yml\n";
      exit(0);
    }
  } catch (const boost::program_options::error &ex) {
    std::cerr << ex.what() << "\n";
  }

  // load the configuration and do the calculation
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