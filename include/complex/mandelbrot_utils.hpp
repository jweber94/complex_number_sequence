#ifndef MANDELBROT_UTILS
#define MANDELBROT_UTILS

#include "complex.hpp"

#include <fstream>
#include <string>
#include <yaml-cpp/yaml.h> // momentan noch für load_run_configuration notwendig --> kann vermutlich bald geloescht werden, weil in c++ includes only notwendig

namespace calculation_utils
{

// util functions
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
                       
int calcNumConvergence(MyComplex &z_i_1, MyComplex &c, int n, double r_c,
                       size_t n_max);

struct new_run_config {
  int calculation_case;
  double x_lower_bound, y_lower_bound; 
  double x_upper_bound, y_upper_bound;
  int N_xmax, N_ymax;
  double R_c;
  double c_0_real, c_0_imag;
  std::string name_result;
  size_t max_iterations;
};

class ConfigurationLoader
{
public: 
  // constructors
  ConfigurationLoader() = delete; 
  ConfigurationLoader(const std::string & path_to_condfig);

  // destructors
  ~ConfigurationLoader() = default; 

  // methods
  const new_run_config get_run_config() const; 

private:
  // members
  new_run_config calc_configuration_; 
};

class CalculationRunner
{
public:
  // constructors
  CalculationRunner() = delete; 
  CalculationRunner(const ConfigurationLoader & config_loader); 

  // destructors
  ~CalculationRunner() = default; 

  // methods
  void run_calculation(); 

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
  std::ofstream output_stream; 
  int (*update_formula_)(MyComplex & z_0, MyComplex & c_0, const double x_0,
                        const double y_0, const double delta_x,
                        const double delta_y, const int i, const int j,
                        double R_c, int maxIterations); 
  MyComplex z_0_; 
  MyComplex c_0_; 

}; 

} // namespace calculation_utils











/* Code before refactoring*/
/*
struct run_config {
  int numIter;
  double x_0, y_0, x_M, y_M;
  int N_xmax, N_ymax;
  int n;
  double R_c;
  double reInsert, imInsert;
  std::string nameResult;
  size_t maxIterations;
};

int calcNumConvergence(MyComplex &z_i_1, MyComplex &c, int n, double r_c,
                       size_t n_max);

void load_run_configuration(YAML::Node &yaml_reader,
                            const run_config &config_struct);

void calculate_convergence_radius(std::ofstream &out_stream,
                                  const run_config &run_configuration);

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
*/
#endif /* MANDELBROT_UTILS */