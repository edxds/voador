//
// Created by Eduardo on 2019-02-23.
//

#include "ui.h"

void flushAndWait() {
    int c;

    do {
        c = getchar();
    } while(c != '\n' && c != EOF);

    printf("Done! Press any key to continue.\n");
    getchar();
}

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
            flushAndWait();
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
            flushAndWait();
            break;
        case UI_CHECK_FLIGHT_PASSENGERS:
            printf("\n");
            showPassengersForFlight();
            flushAndWait();
            break;
        case UI_EXIT:
            printf("Bye!\n");
            break;
        default:
            printf("Option invalid.\n");
            break;
    }
}

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

