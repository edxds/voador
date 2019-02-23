//
// Created by Eduardo on 2019-02-23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "tables.h"

#include "flights.h"
#include "passengers.h"

#ifndef VOADOR_RELATIONS_H
#define VOADOR_RELATIONS_H

extern relation relations[TABLE_SIZE];
extern int currentRelationIndex;

/**
 * Opens relations table and reads the data from the file to the
 * relations array. Also sets the relation index according to the
 * number of relations saved in the file.
 * Calls readTable() from tables.h internally.
 */
void readRelationsTable();

/**
 * Appends relation struct to end of relations.ctable file.
 * Increments current relation index if saving is successful.
 * Calls saveToTable() from tables.h internally.
 *
 * @param relation A pointer to the relation struct to be saved
 */
void saveRelationToTable(relation *relation);

/**
 * Check if there's already a relation registered for the given
 * passenger and flight codes. Prevents relation repetition.
 *
 * @return Returns 1 if a relation is found, 0 otherwise.
 */
int alreadyHasRelation(char passengerCode[], char flightCode[]);

/**
 * Asks user for passenger and flight codes, and then builds
 * a relation by assigning the passenger and flight's code
 * to a relation struct. This struct is then saved to a file
 * that represents the relations table.
 */
void assignPassengerToFlight();

/**
 * Asks user for a passenger code and searches relations
 * with matching codes and displays assigned flight codes
 */
void showFlightsForPassenger();

/**
 * Asks user for a flight code and search relations with
 * matching codes and displays assigned passenger codes
 */
void showPassengersForFlight();

#endif //VOADOR_RELATIONS_H
