cmake_minimum_required(VERSION 2.8)
project(ipoque_wipro)

set(CMAKE_CXX_STANDARD 11)

find_package(yaml-cpp REQUIRED)

add_executable(run_cplx_seq src/main.cpp)
target_include_directories(run_cplx_seq PRIVATE include/complex)
target_link_libraries(run_cplx_seq PRIVATE my_complex yaml-cpp)

add_library(my_complex src/complex.cpp src/complex_seq_utils.cpp)
target_include_directories(my_complex PUBLIC include/complex)