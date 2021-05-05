#include "mandelbrot_utils.hpp"

int calcNumConvergence(MyComplex z_i_1, MyComplex c, int n, double r_c, size_t n_max){

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

// FIXME: Here comes the yaml-parser function