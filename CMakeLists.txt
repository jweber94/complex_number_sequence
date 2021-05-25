cmake_minimum_required(VERSION 2.8)
project(ipoque_wipro)

set(CMAKE_CXX_STANDARD 11)

find_package(yaml-cpp REQUIRED)
find_package(Boost COMPONENTS program_options filesystem REQUIRED)

add_executable(run_cplx_seq src/main.cpp)
target_include_directories(run_cplx_seq PRIVATE include/complex_lib ${Boost_INCLUDE_DIRS})
target_link_libraries(run_cplx_seq PRIVATE my_complex_lib yaml-cpp ${Boost_LIBRARIES})

add_library(my_complex_lib src/complex_lib/complex.cpp src/complex_lib/config_reader.cpp src/complex_lib/calculation_runner.cpp)
target_include_directories(my_complex_lib PUBLIC include/complex_lib)