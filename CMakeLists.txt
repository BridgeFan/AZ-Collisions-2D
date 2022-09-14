cmake_minimum_required(VERSION 3.22)
project(AZ_Collisions2D)

set(CMAKE_CXX_STANDARD 17)

add_executable(AZ_Collisions2D main.cpp Algorithms.cpp Structure.cpp Structure.h Point.cpp MultiTree.h)
