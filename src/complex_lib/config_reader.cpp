#include "config_reader.hpp"
#include <yaml-cpp/yaml.h>

namespace calculation_utils {
// definition of ConfigurationLoader
ConfigurationLoader::ConfigurationLoader(const std::string &path_to_condfig) {
  YAML::Node config_reader = YAML::LoadFile(path_to_condfig);

  this->calc_configuration_.calculation_case = config_reader["case"].as<int>();
  this->calc_configuration_.x_lower_bound = config_reader["x_lower"].as<double>();
  this->calc_configuration_.y_lower_bound = config_reader["y_lower"].as<double>();
  this->calc_configuration_.x_upper_bound = config_reader["x_upper"].as<double>();
  this->calc_configuration_.y_upper_bound = config_reader["y_upper"].as<double>();
  this->calc_configuration_.N_xmax = config_reader["N_xmax"].as<int>();
  this->calc_configuration_.N_ymax = config_reader["N_ymax"].as<int>();
  this->calc_configuration_.R_c = config_reader["R_c"].as<double>();
  this->calc_configuration_.c_0_real = config_reader["c_0_real"].as<double>();
  this->calc_configuration_.c_0_imag = config_reader["c_0_imag"].as<double>();
  this->calc_configuration_.name_result = config_reader["name_result"].as<std::string>();
  this->calc_configuration_.max_iterations = config_reader["max_iter"].as<int>();
}

const new_run_config ConfigurationLoader::get_run_config() const {
  return this->calc_configuration_;
}

} // namespace calculation_utils