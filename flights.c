//
// Created by Eduardo on 2019-02-23.
//

#include "flights.h"

flight flights[TABLE_SIZE];
int currentFlightIndex = 0;

void readFlightsTable() {
    FILE *table = fopen("flights.ctable", "a+");
    if (table == NULL) {
        printf("ERROR: Could not open flights.ctable");
        return;
    }

    fseek(table, 0, SEEK_SET);
    fread(&flights, sizeof(struct flight), TABLE_SIZE, table);

    fseek(table, 0, SEEK_END);
    currentFlightIndex = (int) (ftell(table) / sizeof(struct flight));
}

void saveFlightToTable(flight *flight) {
    FILE *table = fopen("flights.ctable", "a+");
    if (table == NULL) {
        printf("ERROR: Could not save flight.\n");
        return;
    }

    fwrite(flight, sizeof(struct flight), 1, table);
    currentFlightIndex++;
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
