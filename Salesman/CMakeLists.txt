cmake_minimum_required(VERSION 3.15)
project(Salesman)

set(CMAKE_CXX_STANDARD 14)

add_executable(Salesman main.cpp point.h point.cpp tsp.h tsp.cpp Graph.cpp Graph.h)