cmake_minimum_required(VERSION 3.17)
project(shamir)

set(CMAKE_CXX_STANDARD 20)

add_executable(shamir galois256.cpp main.cpp galois256.h Point.cpp Point.h shamir.cpp shamir.h)