cmake_minimum_required(VERSION 2.8)
project(ipoque_wipro)

set(CMAKE_CXX_STANDARD 11)

find_package(yaml-cpp REQUIRED)


add_executable(run_mandelbrot src/main.cpp)
target_include_directories(run_mandelbrot PRIVATE include/complex)
target_link_libraries(run_mandelbrot PRIVATE my_complex)

add_library(my_complex src/complex.cpp src/mandelbrot_utils.cpp)
target_include_directories(my_complex PUBLIC include/complex)