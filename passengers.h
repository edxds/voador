//
// Created by Eduardo on 2019-02-23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

#ifndef VOADOR_PASSENGERS_H
#define VOADOR_PASSENGERS_H

extern passenger passengers[TABLE_SIZE];
extern int currentPassengerIndex;

/**
 * Opens passengers table and reads the data from the file to the
 * passengers array. Also sets the passenger index according to the
 * number of passengers saved in the file.
 */
void readPassengersTable();

/**
 * Appends passenger struct to end of passengers.ctable file.
 * Increments passenger array index if save was successful.
 *
 * @param passenger Pointer to the passenger struct that will be saved.
 */
void savePassengerToTable(passenger *passenger);

/**
 * Function that takes user input, registers a new passenger,
 * and saves it to the passengers table.
 */
void registerPassenger();

/**
 * Finds a passenger with the matching code.
 *
 * @param code The code of the passenger that you want to find.

 * @return A pointer to the found passenger. NULL if the
 * passenger isn't found
 */
passenger* findPassengerForCode(char code[]);

/**
 * Asks user for a passenger code and searches a passenger with
 * the corresponding code and shows its information.
 */
void searchPassenger();

#endif //VOADOR_PASSENGERS_H
