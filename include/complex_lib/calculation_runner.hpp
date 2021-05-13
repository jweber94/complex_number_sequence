#ifndef CALCRUNNER
#define CALCRUNNER

#include "complex.hpp"
#include "config_reader.hpp"
#include <fstream>

namespace calculation_utils {

class CalculationRunner {
public:
  // constructors
  CalculationRunner() = delete;
  CalculationRunner(const ConfigurationLoader &config_loader);

  // destructors
  ~CalculationRunner() = default;

  // methods
  void run_calculation();

  // operators
  friend std::ostream &operator<<(std::ostream &stream, CalculationRunner &cr);

private:
  // methods
  void save_calculation_step(int idx_i, int idx_j, int conv_rad);

  // members
  int case_num_;
  int N_xmax_, N_ymax_;
  double x_lower_bound_, y_lower_bound_;
  double x_upper_bound_, y_upper_bound_;
  double R_c_;
  double c_0_re_, c_0_im_;
  double delta_x_, delta_y_;
  std::string name_result_;
  size_t max_iterations_;
  std::ofstream output_stream_;
  MyComplex z_0_;
  MyComplex c_0_;
  int (*update_formula_)(MyComplex &z_0, MyComplex &c_0, const double x_0,
                         const double y_0, const double delta_x,
                         const double delta_y, const int i, const int j,
                         double R_c, int maxIterations); // function pointer
};

namespace calculation_definitions {
int update_rule_case_1(MyComplex &z_0, MyComplex &c_0, const double x_0,
                       const double y_0, const double delta_x,
                       const double delta_y, const int i, const int j,
                       double R_c, int maxIterations);

int update_rule_case_2(MyComplex &z_0, MyComplex &c_0, const double x_0,
                       const double y_0, const double delta_x,
                       const double delta_y, const int i, const int j,
                       double R_c, int maxIterations);

int update_rule_case_3(MyComplex &z_0, MyComplex &c_0, const double x_0,
                       const double y_0, const double delta_x,
                       const double delta_y, const int i, const int j,
                       double R_c, int maxIterations);

int calc_num_convergence(MyComplex &z_i_1, MyComplex &c, int n, double r_c,
                         size_t n_max);

} // namespace calculation_definitions
} // namespace calculation_utils

#endif /* CALCRUNNER */