#ifndef CONFIGREADER
#define CONFIGREADER

#include "complex.hpp"
#include <string>

namespace calculation_utils {

struct run_config {
  // Interface between ConfigurationLoader class and CalculatonRunner class to
  // decouple the development of the two classes (for extensions in the future)
  int calculation_case;
  double x_lower_bound, y_lower_bound;
  double x_upper_bound, y_upper_bound;
  int N_xmax, N_ymax;
  double R_c;
  double c_0_real, c_0_imag;
  std::string name_result;
  size_t max_iterations;
};

class ConfigurationLoader {
public:
  // constructors
  ConfigurationLoader() = delete;
  ConfigurationLoader(const std::string &path_to_config);

  // destructors
  ~ConfigurationLoader() = default;

  // methods
  const run_config get_run_config() const;

  // operators
  friend std::ostream &operator<<(std::ostream &outstream,
                                  calculation_utils::ConfigurationLoader &cf);

private:
  // members
  run_config calc_configuration_;
  std::string path_;
};
} // namespace calculation_utils

#endif /* CONFIGREADER */