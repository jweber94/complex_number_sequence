#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <yaml-cpp/yaml.h>

#include "complex.hpp"
#include "mandelbrot_utils.cpp"

int main (){

	using namespace std;

	// parse the config for the run
	std::string config_path;
	// std::cout << "Please insert the input path\n";  
	// std::cin >> config_path; 
	// std::cout << "\n"; 
	config_path = "/home/jens/Schreibtisch/ipoque/ipoque_wipro/etc/mandelbrot_config.yml"; // debug

	YAML::Node config_reader = YAML::LoadFile(config_path); 

	run_config config_vars; 
	ofstream resultStream;

	load_run_configuration(config_reader, config_vars); 

	cout << "Calculation started, please wait!" << endl;  
	switch(config_vars.numIter){
		case 1: 					
		{
			// z_i+1 = z_i^2 + c, with c = const

			// I should do something to make proper use of the switch case statement - right now, the config file is sufficient
			calculate_convergence_radius(resultStream, config_vars); 
			break;
		}
		case 2:							
		{
			// z_i+1 = z_i^2 + c, with c = n_x*delta_x + i*n_y*delta_y
			// FIXME
			
			/*
			MyComplex z_0(config_vars.reInsert, config_vars.imInsert);
			MyComplex c_0(config_vars.x_0, config_vars.y_0);

			resultStream.open(config_vars.nameResult);

			for (int k = 0; k <= config_vars.N_xmax; k++){
				for (int l = 0; l <= config_vars.N_ymax; l++){
					c_0.setRe(config_vars.x_0+delta_x*double(k));
					c_0.setIm(config_vars.y_0+delta_y*double(l));
					n_iter_temp = calcNumConvergence(z_0, c_0, config_vars.n, config_vars.R_c, config_vars.maxIterations);

					if (resultStream.is_open())
					{
						resultStream << k << " " << l << " " << n_iter_temp << endl; // unten an das File anhaengen
					}
					else
					{
						cout << "Es ist ein Fehler aufgetreten. Das Programm wird beendet. Bitte ueberpruefen Sie den Quellcode!" << endl;
						exit(0);
					}
				}
				resultStream << endl;
			}
			resultStream.close();
			*/
			break;
		}
		case 3:								
		{
			// z_i+1 = z_i^4 + c, with c = c = n_x*delta_x + i*n_y*delta_y
			
			// FIXME
			
			/*
			MyComplex z_0(config_vars.reInsert, config_vars.imInsert);
			MyComplex c_0(config_vars.x_0, config_vars.y_0);

			resultStream.open(config_vars.nameResult);

			for (int m = 0; m <= config_vars.N_xmax; m++){
				for (int n_i = 0; n_i <= config_vars.N_ymax; n_i++){
					c_0.setRe(config_vars.x_0+delta_x*double(m));
					c_0.setIm(config_vars.y_0+delta_y*double(n_i));
					n_iter_temp = calcNumConvergence(z_0, c_0, config_vars.n, config_vars.R_c, config_vars.maxIterations);
					if (resultStream.is_open())
					{
						resultStream << m << " " << n_i << " " << n_iter_temp << endl;
					}
					else
					{
						cout << "Es ist ein Fehler aufgetreten. Das Programm wird beendet. Bitte ueberpruefen Sie den Quellcode!" << endl;
						exit(0);
					}
				}
				resultStream<<endl;
			}
			resultStream.close();
			*/
			break;
		}
		default:
		{
			cout << config_vars.numIter << " ist kein zulaessiger Wert fuer die Iterationsvorschrift! Das Programm wird beendet" << endl;
			exit(0);
		}
	}
};
