#ifndef MANDELBROT_UTILS
#define MANDELBROT_UTILS

#include "complex.hpp"

#include <cstddef>

int calcNumConvergence(MyComplex z_i_1, MyComplex c, int n, double r_c, size_t n_max);

// FIXME: Here comes the yaml parser

#endif /* MANDELBROT_UTILS */