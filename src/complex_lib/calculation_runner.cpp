#include "calculation_runner.hpp"
#include <iostream>
#include <stdlib.h>

namespace calculation_utils {

CalculationRunner::CalculationRunner(const ConfigurationLoader &config_loader) {
  new_run_config temp_run_config = config_loader.get_run_config();

  // set the run member variables based on the given config
  this->case_num_ = temp_run_config.calculation_case;
  this->x_lower_bound_ = temp_run_config.x_lower_bound;
  this->y_lower_bound_ = temp_run_config.y_lower_bound;
  this->x_upper_bound_ = temp_run_config.x_upper_bound;
  this->y_upper_bound_ = temp_run_config.y_upper_bound;
  this->N_xmax_ = temp_run_config.N_xmax;
  this->N_ymax_ = temp_run_config.N_ymax;
  this->R_c_ = temp_run_config.R_c;
  this->c_0_re_ = temp_run_config.c_0_real;
  this->c_0_im_ = temp_run_config.c_0_imag;
  this->name_result_ = temp_run_config.name_result;
  this->max_iterations_ = temp_run_config.max_iterations;

  // calculate run parameters based on the given config
  this->delta_x_ =
      (this->x_upper_bound_ - this->x_lower_bound_) / double(this->N_xmax_);
  this->delta_y_ =
      (this->y_upper_bound_ - this->y_lower_bound_) / double(this->N_ymax_);

  // set update rule and start values based on the given config
  switch (temp_run_config.calculation_case) {
  case 1: {
    this->z_0_.setRe(this->x_lower_bound_);
    this->z_0_.setIm(this->y_lower_bound_);
    this->c_0_.setRe(this->c_0_re_);
    this->c_0_.setIm(this->c_0_im_);
    this->update_formula_ = calculation_definitions::update_rule_case_1;
    break;
  }
  case 2: {
    this->z_0_.setRe(this->c_0_re_);
    this->z_0_.setIm(this->c_0_im_);
    this->c_0_.setRe(this->x_lower_bound_);
    this->c_0_.setIm(this->y_lower_bound_);
    this->update_formula_ = calculation_definitions::update_rule_case_2;
    break;
  }
  case 3: {
    this->z_0_.setRe(this->c_0_re_);
    this->z_0_.setIm(this->c_0_im_);
    this->c_0_.setRe(this->x_lower_bound_);
    this->c_0_.setIm(this->y_lower_bound_);
    this->update_formula_ = calculation_definitions::update_rule_case_3;
    break;
  }
  default: {
    std::cout
        << this->case_num_
        << " is no valid calculation case number. The program will end now.\n";
    exit(0);
  }
  }
}

void CalculationRunner::run_calculation() {
  int temp_conv_rad;
  this->output_stream_.open(this->name_result_);

  for (int i = 0; i <= this->N_xmax_; i++) {
    for (int j = 0; j <= this->N_ymax_; j++) {
      // main calculation
      temp_conv_rad = this->update_formula_(
          this->z_0_, this->c_0_, this->x_lower_bound_, this->y_lower_bound_,
          this->delta_x_, this->delta_y_, i, j, this->R_c_,
          this->max_iterations_);
      // write step result to file
      this->save_calculation_step(i, j, temp_conv_rad);
    }
  }
  this->output_stream_.close();
}

void CalculationRunner::save_calculation_step(int idx_i, int idx_j,
                                              int conv_rad) {
  if (this->output_stream_.is_open()) {
    this->output_stream_ << idx_i << " " << idx_j << " " << conv_rad << "\n";
  } else {
    std::cerr << "ERROR: No result stream for saving the calculation "
                 "result was found. Please check mandelbrot_utils.cpp"
              << "\n";
    exit(0);
  }
}

namespace calculation_definitions {
int calc_num_convergence(MyComplex &z_i_1, MyComplex &c, int n, double r_c,
                       size_t n_max) {
  MyComplex resultIteration_i = z_i_1;

  // convergency calculation
  for (size_t i = 0; i < n_max; i++) {
    resultIteration_i = (resultIteration_i ^ n) + c;
    if (resultIteration_i.norm() >= r_c) { // calc num iterations until convergence
      return i;
    }
  }
  return n_max; // default value if not converged
};

int update_rule_case_1(MyComplex &z_0, MyComplex &c_0, const double x_0,
                       const double y_0, const double delta_x,
                       const double delta_y, const int i, const int j,
                       double R_c, int maxIterations) {
  // z_i+1 = z_i^2 + c
  // , with c = const and z_{0} = n_{x} \delta_{x} + i n_{y} \delta_{x}
  int step_result;

  z_0.setRe(x_0 + delta_x * double(i));
  z_0.setIm(y_0 + delta_y * double(j));
  step_result = calc_num_convergence(
      z_0, c_0, 2, R_c, maxIterations); // 2 is for the exponent z_i^2

  return step_result;
}

int update_rule_case_2(MyComplex &z_0, MyComplex &c_0, const double x_0,
                       const double y_0, const double delta_x,
                       const double delta_y, const int i, const int j,
                       double R_c, int maxIterations) {
  // z_i+1 = z_i^2 + c, with c = n_x*delta_x + i*n_y*delta_y and z_0 = 0 + i 0
  int step_result;

  c_0.setRe(x_0 + delta_x * double(i));
  c_0.setIm(y_0 + delta_y * double(j));
  step_result = calc_num_convergence(z_0, c_0, 2, R_c, maxIterations);

  return step_result;
}

int update_rule_case_3(MyComplex &z_0, MyComplex &c_0, const double x_0,
                       const double y_0, const double delta_x,
                       const double delta_y, const int i, const int j,
                       double R_c, int maxIterations) {
  // z_i+1 = z_i^4 + c
  // , with c = c = n_x*delta_x + i*n_y*delta_y and z_0 = 0 + i 0
  int step_result;

  c_0.setRe(x_0 + delta_x * double(i));
  c_0.setIm(y_0 + delta_y * double(j));
  step_result = calc_num_convergence(z_0, c_0, 4, R_c, maxIterations);

  return step_result;
}
} // namespace calculation_rules
} // namespace calculation_utils