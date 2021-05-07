#include "mandelbrot_utils.hpp"

#include <iostream>

void load_run_configuration(YAML::Node &yaml_reader,
                            run_config &config_struct) {
  // Iteration over struct members is not useful due to the different datatypes
  // of the entrys
  config_struct.numIter = yaml_reader["numIter"].as<int>();
  config_struct.x_0 = yaml_reader["x_0"].as<double>();
  config_struct.y_0 = yaml_reader["y_0"].as<double>();
  config_struct.x_M = yaml_reader["x_M"].as<double>();
  config_struct.y_M = yaml_reader["y_M"].as<double>();
  config_struct.N_xmax = yaml_reader["N_xmax"].as<int>();
  config_struct.N_ymax = yaml_reader["N_ymax"].as<int>();
  config_struct.R_c = yaml_reader["R_c"].as<double>();
  config_struct.reInsert = yaml_reader["reInsert"].as<double>();
  config_struct.imInsert = yaml_reader["imInsert"].as<double>();
  config_struct.nameResult = yaml_reader["nameResult"].as<std::string>();
  config_struct.maxIterations = yaml_reader["maxIterations"].as<int>();
}

int calcNumConvergence(MyComplex &z_i_1, MyComplex &c, int n, double r_c,
                       size_t n_max) {

  MyComplex resultIteration_i = z_i_1;

  // convergence calculation
  for (size_t i = 0; i < n_max; i++) {
    resultIteration_i = (resultIteration_i ^ n) + c;
    if (resultIteration_i.norm() >= r_c) { // termination condition
      return i;
    }
  }
  return n_max;
};

int update_rule_case_1(MyComplex &z_0, MyComplex &c_0, const double x_0,
                       const double y_0, const double delta_x,
                       const double delta_y, const int i, const int j,
                       double R_c, int maxIterations) {
  // z_i+1 = z_i^2 + c, with c = const
  int step_result;

  z_0.setRe(x_0 + delta_x * double(i));
  z_0.setIm(y_0 + delta_y * double(j));
  step_result = calcNumConvergence(
      z_0, c_0, 2, R_c, maxIterations); // 2 is for the exponent z_i^2

  return step_result;
}

int update_rule_case_2(MyComplex &z_0, MyComplex &c_0, const double x_0,
                       const double y_0, const double delta_x,
                       const double delta_y, const int i, const int j,
                       double R_c, int maxIterations) {
  // z_i+1 = z_i^2 + c, with c = n_x*delta_x + i*n_y*delta_y
  int step_result;

  c_0.setRe(x_0 + delta_x * double(i));
  c_0.setIm(y_0 + delta_y * double(j));
  step_result = calcNumConvergence(z_0, c_0, 2, R_c, maxIterations);

  return step_result;
}

int update_rule_case_3(MyComplex &z_0, MyComplex &c_0, const double x_0,
                       const double y_0, const double delta_x,
                       const double delta_y, const int i, const int j,
                       double R_c, int maxIterations) {
  // z_i+1 = z_i^4 + c, with c = c = n_x*delta_x + i*n_y*delta_y
  int step_result;

  c_0.setRe(x_0 + delta_x * double(i));
  c_0.setIm(y_0 + delta_y * double(j));
  step_result = calcNumConvergence(z_0, c_0, 4, R_c, maxIterations);

  return step_result;
}

void calculate_convergence_radius(std::ofstream &out_stream,
                                  const run_config &run_configuration) {
  // function pointer as parameter function
  double delta_x;
  double delta_y;
  int n_iter_temp;
  MyComplex z_0{};
  MyComplex c_0{};
  int (*update_formula)(MyComplex & z_0, MyComplex & c_0, const double x_0,
                        const double y_0, const double delta_x,
                        const double delta_y, const int i, const int j,
                        double R_c, int maxIterations);

  // calculate the step sizes based on the given parameters
  delta_x = (run_configuration.x_M - run_configuration.x_0) /
            double(run_configuration.N_xmax);
  delta_y = (run_configuration.y_M - run_configuration.y_0) /
            double(run_configuration.N_ymax);

  out_stream.open(run_configuration.nameResult);

  // get the correct update rule TODO: Create function for this
  switch (run_configuration.numIter) {
  case 1: {
    // set start values
    z_0.setRe(run_configuration.x_0);
    z_0.setIm(run_configuration.y_0);
    c_0.setRe(run_configuration.reInsert);
    c_0.setIm(run_configuration.imInsert);

    // set the update rule
    update_formula = update_rule_case_1;

    break;
  }
  case 2: {
    z_0.setRe(run_configuration.reInsert);
    z_0.setIm(run_configuration.imInsert);
    c_0.setRe(run_configuration.x_0);
    c_0.setIm(run_configuration.y_0);

    update_formula = update_rule_case_2;

    break;
  }
  case 3: {
    z_0.setRe(run_configuration.reInsert);
    z_0.setIm(run_configuration.imInsert);
    c_0.setRe(run_configuration.x_0);
    c_0.setIm(run_configuration.y_0);

    update_formula = update_rule_case_3;

    break;
  }
  default: {
    std::cout
        << run_configuration.numIter
        << " is no valid calculation case number. The program will end now.\n";
    exit(0);
  }
  }

  // iteration over the complex number sequence
  for (int i = 0; i <= run_configuration.N_xmax; i++) {
    for (int j = 0; j <= run_configuration.N_ymax; j++) {

      n_iter_temp =
          update_formula(z_0, c_0, run_configuration.x_0, run_configuration.y_0,
                         delta_x, delta_y, i, j, run_configuration.R_c,
                         run_configuration.maxIterations);

      // save the iteration result
      if (out_stream.is_open()) {
        out_stream << i << " " << j << " " << n_iter_temp << "\n";
      } else {
        std::cerr << "ERROR: No result stream for saving the calculation "
                     "result was found. Please check mandelbrot_utils.cpp"
                  << "\n";
        exit(0);
      }
    }
  }
  out_stream.close();
}