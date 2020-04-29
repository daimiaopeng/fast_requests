cmake_minimum_required (VERSION 3.5)
project ("fast_requetst")

SET(CMAKE_BUILD_TYPE "Release")

find_package(pybind11 CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)

pybind11_add_module(fast_requetst_cpp main.cpp)
 target_link_libraries(fast_requetst_cpp PRIVATE  cpr pybind11::embed pybind11::module pybind11::pybind11)