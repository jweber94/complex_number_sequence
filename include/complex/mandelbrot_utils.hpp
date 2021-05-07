#ifndef MANDELBROT_UTILS
#define MANDELBROT_UTILS

#include "complex.hpp"

#include <fstream>
#include <yaml-cpp/yaml.h>

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

#endif /* MANDELBROT_UTILS */