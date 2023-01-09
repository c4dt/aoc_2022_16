cmake_minimum_required(VERSION 3.23)
project(aoc_2022_16)

set(CMAKE_CXX_STANDARD 20)

add_executable(aoc_2022_16 main.cpp Tunnels.cpp Tunnels.h NumericVector.cpp NumericVector.h Solve.tpp Solve.h OnePerson.cpp OnePerson.h TwoPersons.cpp TwoPersons.h Route.cpp Route.h)
