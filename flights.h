//
// Created by Eduardo on 2019-02-23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

#ifndef VOADOR_FLIGHTS_H
#define VOADOR_FLIGHTS_H

extern flight flights[TABLE_SIZE];
extern int currentFlightIndex;

/**
 * Opens flights table and reads the data from the file to the
 * flights array. Also sets the flight index according to the
 * number of flights saved in the file.
 */
void readFlightsTable();

/**
 * Appends flight struct to end of flights.ctable file.
 * Increments flight array index if save was successful.
 *
 * @param flight Pointer to the flight struct that will be saved.
 */
void saveFlightToTable(flight *flight);

/**
 * Function that takes user input, registers a new flight,
 * and saves it to the flights table.
 */
void registerFlight();

/**
 * Looks through the flights array to find a flight struct
 * with a code that matches the code passed to the function.
 *
 * @param code The code of the flight that you want to find.

 * @return A pointer to the found flight. NULL if the
 * flight isn't found
 */
flight* findFlightForCode(char code[]);

/**
 * Asks user for a flight code and searches a flight with
 * the corresponding code and shows its information.
 */
void searchFlight();

#endif //VOADOR_FLIGHTS_H
