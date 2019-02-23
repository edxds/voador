cmake_minimum_required(VERSION 3.13)
project(Voador C)

set(CMAKE_C_STANDARD 99)

add_executable(Voador main.c structs.h passengers.c passengers.h flights.c flights.h)