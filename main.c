#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "passengers.h"
#include "flights.h"
#include "relations.h"

#define UI_IDLE                     0
#define UI_REGISTER_PASSENGER       1
#define UI_REGISTER_FLIGHT          2
#define UI_SEARCH_PASSENGER         3
#define UI_SEARCH_FLIGHT            4
#define UI_ASSIGN_PASSENGER         5
#define UI_CHECK_PASSENGER_FLIGHTS  6
#define UI_CHECK_FLIGHT_PASSENGERS  7
#define UI_EXIT                     -1

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
            flushAndWait();
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