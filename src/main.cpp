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
	std::cout << "Please insert the input path\n";  
	std::cin >> config_path; 
	std::cout << "\n"; 

	YAML::Node config = YAML::LoadFile(config_path); 

	// variables
	int numIter;
	double x_0, y_0, x_M, y_M;
	int N_xmax, N_ymax;
	int n;
	double R_c;
	double reInsert, imInsert;
	double delta_x, delta_y;
	string nameResult;
	size_t maxIterations;

	int n_iter_temp;
	ofstream resultStream;	


	std::cout << "This is the number of iterations: " << config['n'].as<int>() << " - should be 2000\n"; 
	std::cout << "CAUTION: DEBUG END\n"; 

	// Einlesen der Uerbergabeparameter
	cout << "Bitte Nummer der Iteratotionsvorschrift eingeben" << endl;
	cin>>numIter;

	cout << "Bitte Wertebereich eingeben" << endl;
	cout << "(x_0, y_0): " << endl;
	cin >> x_0 >> y_0;

	cout << "(x_M, y_M): " << endl;
	cin >> x_M >> y_M;

	cout << "Bitte Unterteilung festlegen (N_xmax, N_ymax): " << endl;
	cin >> N_xmax >> N_ymax;

	cout << "Bitte Exponent eingeben: " << endl;
	cin >> n;

	cout << "Bitte maximale Anzahl an Iterationen eingeben: " << endl;
	cin >> maxIterations;

	cout << "Bitte Konvergenzradius eingeben: " << endl;
	cin >> R_c;

	cout << "Name der Ergebnisdatei eingeben: " << endl;
	cin >> nameResult;

	cout << "Bitte Realanteil und Imaginaeranteil der komplexen Zahl c_0 eingeben: " << endl;
	cin >> reInsert >> imInsert;

	// Berechnung der Schrittweite
	delta_x = (x_M-x_0)/double(N_xmax);
	delta_y = (y_M-y_0)/double(N_ymax);

	cout << "Berechne! Bitte warten!" << endl;  

	switch(numIter){
		case 1: 					// Iterationsvorschrift 1
		{
			MyComplex z_0(x_0, y_0);
			MyComplex c_0(reInsert, imInsert);

			resultStream.open(nameResult);

			// Iteration ueber alle Anfangsbedingungen der komplexen Zahlenfolge
			for (int i = 0; i <= N_xmax; i++){
				for (int j = 0; j <= N_ymax; j++){
					z_0.setRe(x_0+delta_x*double(i));
					z_0.setIm(y_0+delta_y*double(j));

					n_iter_temp = calcNumConvergence(z_0, c_0, n, R_c, maxIterations);

					// Schreibe in Ergebnisdatei
					if (resultStream.is_open()) // Sicherheitsabfrage, ob Datei zum Schreiben bereit ist
					{
						resultStream << i << " " << j << " " << n_iter_temp << endl;
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
			break;
		}
		case 2:							// Iterationsvorschrift 2
		{
			MyComplex z_0(reInsert, imInsert);
			MyComplex c_0(x_0, y_0);

			resultStream.open(nameResult);

			for (int k = 0; k <= N_xmax; k++){
				for (int l = 0; l <= N_ymax; l++){
					c_0.setRe(x_0+delta_x*double(k));
					c_0.setIm(y_0+delta_y*double(l));
					n_iter_temp = calcNumConvergence(z_0, c_0, n, R_c, maxIterations);

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
			break;
		}
		case 3:								// Iterationsvorschrift 3
		{
			MyComplex z_0(reInsert, imInsert);
			MyComplex c_0(x_0, y_0);

			resultStream.open(nameResult);

			for (int m = 0; m <= N_xmax; m++){
				for (int n = 0; n <= N_ymax; n++){
					c_0.setRe(x_0+delta_x*double(m));
					c_0.setIm(y_0+delta_y*double(n));
					n_iter_temp = calcNumConvergence(z_0, c_0, n, R_c, maxIterations);
					if (resultStream.is_open())
					{
						resultStream << m << " " << n << " " << n_iter_temp << endl;
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
			break;
		}
		default:
		{
			cout << numIter << " ist kein zulaessiger Wert fuer die Iterationsvorschrift! Das Programm wird beendet" << endl;
			exit(0);
		}
	}
};
