cmake_minimum_required (VERSION 3.8)
project ("fast_requetst")
find_package(pybind11 CONFIG REQUIRED)

find_package(cpr CONFIG REQUIRED)

pybind11_add_module(fast_requetst_cpp main.cpp)
 target_link_libraries(fast_requetst_cpp PRIVATE  cpr pybind11::embed pybind11::module pybind11::pybind11)
