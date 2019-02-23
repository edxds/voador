//
// Created by Eduardo on 2019-02-23.
//

#include "flights.h"

flight flights[TABLE_SIZE];
int currentFlightIndex = 0;

void readFlightsTable() {
    readTable("flights", sizeof(struct flight), &flights, &currentFlightIndex);
}

void saveFlightToTable(flight *flight) {
    saveToTable("flights", sizeof(struct flight), flight, &currentFlightIndex);
}

void registerFlight() {
    printf(" -- Register flight\n");

    printf("Code: ");
    scanf("%s", flights[currentFlightIndex].code);

    printf("Origin: ");
    scanf("%s", flights[currentFlightIndex].origin);

    printf("Destination: ");
    scanf("%s", flights[currentFlightIndex].destination);

    saveFlightToTable(&flights[currentFlightIndex]);
}

flight* findFlightForCode(char code[]) {
    int currentPosition = 0;
    flight *currentFlight = &flights[currentPosition];

    /*
     * While the current flight's code isn't equal
     * to the code requested
     */
    while (strcmp(currentFlight->code, code) != 0) {
        currentPosition++;
        if (currentPosition > currentFlightIndex) {
            // Exit the loop if we're out of bounds
            return NULL;
        }

        currentFlight = &flights[currentPosition];
    }

    return currentFlight;
}

void searchFlight() {
    char code[CODE_LENGTH];

    printf("Enter flight code: ");
    scanf("%s", code);

    flight *foundFlight = findFlightForCode(code);
    if (foundFlight == NULL) {
        printf("Flight not found.\n");
        return;
    }

    printf("   -- Flight %s\n", foundFlight->code);
    printf("Origin: %s\n", foundFlight->origin);
    printf("Destination: %s\n", foundFlight->destination);
}
