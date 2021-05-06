#include "mandelbrot_utils.hpp"

#include <iostream>

int calcNumConvergence(MyComplex & z_i_1, MyComplex & c, int n, double r_c, size_t n_max){

	using namespace std;

	MyComplex resultIteration_i = z_i_1;

    // convergence calculation
	for (size_t i = 0; i < n_max; i++){
		resultIteration_i = (resultIteration_i^n) + c;
		if (resultIteration_i.norm() >= r_c ){ 	// termination condition
			return i;
		}
	}
	return n_max;
};

void load_run_configuration(YAML::Node & yaml_reader, run_config & config_struct)
{
	// TODO: convert this to a for loop with iteration over the strings
	config_struct.numIter = yaml_reader["numIter"].as<int>(); // choose calculation rule
	config_struct.x_0 = yaml_reader["x_0"].as<double>();  
	config_struct.y_0 = yaml_reader["y_0"].as<double>(); 
	config_struct.x_M = yaml_reader["x_M"].as<double>(); 
	config_struct.y_M = yaml_reader["y_M"].as<double>();
	config_struct.N_xmax = yaml_reader["N_xmax"].as<int>();
	config_struct.N_ymax = yaml_reader["N_ymax"].as<int>();
	config_struct.n = yaml_reader["n"].as<int>(); // exponnent TODO: pull the exponent out and create a function pointer to show my skills ;-) 
	config_struct.R_c = yaml_reader["R_c"].as<double>();
	config_struct.reInsert = yaml_reader["reInsert"].as<double>(); 
	config_struct.imInsert = yaml_reader["imInsert"].as<double>();
	config_struct.nameResult = yaml_reader["nameResult"].as<std::string>();
	config_struct.maxIterations = yaml_reader["maxIterations"].as<int>();
}

void calculate_convergence_radius(std::ofstream & out_stream, const run_config & run_configuration)
{
	double delta_x; 
	double delta_y;
	int n_iter_temp;
	MyComplex z_0(run_configuration.x_0, run_configuration.y_0);
	MyComplex c_0(run_configuration.reInsert, run_configuration.imInsert);

	// calculate the step sizes based on the given parameters
	delta_x = (run_configuration.x_M-run_configuration.x_0)/double(run_configuration.N_xmax);
	delta_y = (run_configuration.y_M-run_configuration.y_0)/double(run_configuration.N_ymax);

	out_stream.open(run_configuration.nameResult);

	// iteration over the complex number sequence
	for (int i = 0; i <= run_configuration.N_xmax; i++){
		for (int j = 0; j <= run_configuration.N_ymax; j++){
			z_0.setRe(run_configuration.x_0+delta_x*double(i));
			z_0.setIm(run_configuration.y_0+delta_y*double(j));

			n_iter_temp = calcNumConvergence(z_0, c_0, run_configuration.n, run_configuration.R_c, run_configuration.maxIterations);

			// save the result TODO: Make a save result function for this 
			if (out_stream.is_open())
			{
				out_stream << i << " " << j << " " << n_iter_temp << "\n";
			}
			else
			{
				std::cerr << "ERROR: No result stream for saving the calculation result was found. Please check mandelbrot_utils.cpp" << "\n";
				exit(0);
			}
		}
		out_stream<<"\n";
	}
	out_stream.close();
	
}