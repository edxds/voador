cmake_minimum_required(VERSION 3.13)
project(Voador C)

set(CMAKE_C_STANDARD 99)

add_executable(Voador src/main.c src/structs.h src/passengers.c src/passengers.h src/flights.c src/flights.h src/relations.c src/relations.h src/ui.c src/ui.h src/tables.c src/tables.h)