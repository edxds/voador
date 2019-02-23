#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "passengers.h"
#include "flights.h"

#define UI_IDLE                     0
#define UI_REGISTER_PASSENGER       1
#define UI_REGISTER_FLIGHT          2
#define UI_SEARCH_PASSENGER         3
#define UI_SEARCH_FLIGHT            4
#define UI_ASSIGN_PASSENGER         5
#define UI_CHECK_PASSENGER_FLIGHTS  6
#define UI_CHECK_FLIGHT_PASSENGERS  7
#define UI_EXIT                     -1

relation relations[TABLE_SIZE];

int currentRelationIndex = 0;

/**
 * Function used to stop flow and wait for user input.
 * We need to flush the input buffer, otherwise getchar
 * would return immediately (e.g.: after using scanf())
 */
void flushAndWait() {
    int c;

    do {
        c = getchar();
    } while(c != '\n' && c != EOF);

    printf("Done! Press any key to continue.\n");
    getchar();
}

/**
 * Opens relations table and reads the data from the file to the
 * relations array. Also sets the relation index according to the
 * number of relations saved in the file.
 */
void readRelationsTable() {
    FILE *table = fopen("relations.ctable", "a+");
    if (table == NULL) {
        printf("ERROR: Could not open relations.ctable");
        return;
    }

    fseek(table, 0, SEEK_SET);
    fread(&relations, sizeof(struct relation), TABLE_SIZE, table);

    fseek(table, 0, SEEK_END);
    currentRelationIndex = (int) (ftell(table) / sizeof(struct relation));
}

/**
 * Appends relation struct to end of relations.ctable file.
 *
 * @param relation A pointer to the relation struct to be saved
 */
void saveRelationToTable(relation *relation) {
    FILE *table = fopen("relations.ctable", "a+");
    if (table == NULL) {
        printf("ERROR: Could not save assignment.\n");
    } else {
        fwrite(relation, sizeof(struct relation), 1, table);
    }
}

/**
 * Check if there's already a relation registered for the given
 * passenger and flight codes. Prevents relation repetition.
 *
 * @return Returns 1 if a relation is found, 0 otherwise.
 */
int alreadyHasRelation(char passengerCode[], char flightCode[]) {
    int i = 0;
    for (i; i <= currentRelationIndex; i++) {
        relation currentRelation = relations[i];

        if (strcmp(currentRelation.code_passenger, passengerCode) == 0
            && strcmp(currentRelation.code_flight, flightCode) == 0) {
            return 1;
        }
    }

    return 0;
}

/**
 * Builds a relation between passenger and flight,
 * by assigning the passenger and flight's code to
 * a relation struct. This struct is then saved to
 * a file that represents the relations table.
 */
void assignPassengerToFlight() {
    char passengerCode[CODE_LENGTH], flightCode[CODE_LENGTH];

    printf(" -- Assign Passenger\n");

    printf("Passenger code: ");
    scanf("%s", passengerCode);

    printf("Flight code: ");
    scanf("%s", flightCode);

    if (alreadyHasRelation(passengerCode, flightCode)) {
        printf("Passenger already assigned to flight!\n");
        return;
    }

    // Return if the passenger or the flight doesn't exist
    if (findPassengerForCode(passengerCode) == NULL) {
        printf("Passenger not found.\n");
        return;
    }

    if (findFlightForCode(flightCode) == NULL) {
        printf("Flight not found.\n");
        return;
    }

    strcpy(relations[currentRelationIndex].code_flight, flightCode);
    strcpy(relations[currentRelationIndex].code_passenger, passengerCode);

    saveRelationToTable(&relations[currentRelationIndex]);
    currentRelationIndex++;

    printf("Assigned passenger %s to flight %s.\n", passengerCode, flightCode);
    flushAndWait();
}

/**
 * Asks user for a passenger code and searches relations
 * with matching codes and displays assigned flight codes
 */
void showFlightsForPassenger() {
    char code[CODE_LENGTH];
    printf("Enter passenger code: ");
    scanf("%s", code);

    passenger *passenger = findPassengerForCode(code);
    if (passenger == NULL) {
        printf("Passenger not found.\n");
        return;
    }

    printf(" -- Passenger %s's flights\n", passenger->code);

    int hasFoundAtLeastOneFlight = 0;
    int i = 0;

    for (i; i <= currentRelationIndex; i++) {
        relation currentRelation = relations[i];
        if (strcmp(passenger->code, currentRelation.code_passenger) == 0) {
            // Found relation that contains matching passenger code.
            hasFoundAtLeastOneFlight = 1;

            printf("Flight %s\n", currentRelation.code_flight);
        }
    }

    if (!hasFoundAtLeastOneFlight) {
        printf("Passenger hasn't been assigned to any flights yet.\n");
    }
}

/**
 * Asks user for a flight code and search relations with
 * matching codes and displays assigned passenger codes
 */
void showPassengersForFlight() {
    char code[CODE_LENGTH];
    printf("Enter flight code: ");
    scanf("%s", code);

    flight *flight = findFlightForCode(code);
    if (flight == NULL) {
        printf("Flight not found.\n");
        return;
    }

    printf(" -- Flight %s's passengers\n", flight->code);

    int hasFoundAtLeastOnePassenger = 0;
    int i = 0;

    for (i; i <= currentRelationIndex; i++) {
        relation currentRelation = relations[i];
        if (strcmp(flight->code, currentRelation.code_flight) == 0) {
            // Found relation that contains matching flight code.
            hasFoundAtLeastOnePassenger = 1;

            printf("Passenger %s\n", currentRelation.code_passenger);
        }
    }

    if (!hasFoundAtLeastOnePassenger) {
        printf("No passengers were assigned to this flight yet.");
    }
}

/**
 * Function that runs the function associated
 * with the menu option that the user choose.
 *
 * @param option User's menu option
 */
void handleMenuOption(int option) {
    switch(option) {
        case UI_REGISTER_PASSENGER:
            printf("\n");
            registerPassenger();
            flushAndWait();
            break;
        case UI_REGISTER_FLIGHT:
            printf("\n");
            registerFlight();
            flushAndWait();
            break;
        case UI_SEARCH_PASSENGER:
            printf("\n");
            searchPassenger();
            break;
        case UI_SEARCH_FLIGHT:
            printf("\n");
            searchFlight();
            break;
        case UI_ASSIGN_PASSENGER:
            printf("\n");
            assignPassengerToFlight();
            break;
        case UI_CHECK_PASSENGER_FLIGHTS:
            printf("\n");
            showFlightsForPassenger();
            break;
        case UI_CHECK_FLIGHT_PASSENGERS:
            printf("\n");
            showPassengersForFlight();
            break;
        case UI_EXIT:
            printf("Bye!\n");
            break;
        default:
            printf("Option invalid.\n");
            break;
    }
}

/**
 * Function that runs as long as the user doesn't input -1.
 * Calls handleMenuOption after user inputs option.
 */
void runUiLoop() {
    int currentState = UI_IDLE;

    while (currentState != UI_EXIT) {
        printf("\nMenu: \n");

        printf("%d: Register Passenger\n", UI_REGISTER_PASSENGER);
        printf("%d: Register Flight\n", UI_REGISTER_FLIGHT);
        printf("%d: Search Passenger\n", UI_SEARCH_PASSENGER);
        printf("%d: Search Flight\n", UI_SEARCH_FLIGHT);
        printf("%d: Assign Passenger\n", UI_ASSIGN_PASSENGER);
        printf("%d: Check Passenger's Flights\n", UI_CHECK_PASSENGER_FLIGHTS);
        printf("%d: Check Flight's Passengers", UI_CHECK_FLIGHT_PASSENGERS);

        printf("\nInput (%d) to exit: ", UI_EXIT);
        scanf("%d", &currentState);

        handleMenuOption(currentState);
    }
}

int main() {
    readPassengersTable();
    readFlightsTable();
    readRelationsTable();

    runUiLoop();
}