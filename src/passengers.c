//
// Created by Eduardo on 2019-02-23.
//

#include "passengers.h"

passenger passengers[TABLE_SIZE];
int currentPassengerIndex = 0;

void readPassengersTable() {
    readTable("passengers", sizeof(struct passenger), &passengers, &currentPassengerIndex);
}

void savePassengerToTable(passenger *passenger) {
    saveToTable("passengers", sizeof(struct passenger), passenger, &currentPassengerIndex);
}

void registerPassenger() {
    printf("   -- Register passenger\n");

    printf("Name: ");
    scanf("%s", passengers[currentPassengerIndex].name);

    printf("Code: ");
    scanf("%s", passengers[currentPassengerIndex].code);

    savePassengerToTable(&passengers[currentPassengerIndex]);
}

passenger* findPassengerForCode(char code[]) {
    int currentPosition = 0;
    passenger *currentPassenger = &passengers[currentPosition];

    /*
     * While the current passenger's code
     * is not equal to the code requested
     */
    while (strcmp(currentPassenger->code, code) != 0) {
        currentPosition++;
        if (currentPosition > currentPassengerIndex) {
            // Exit the loop if we're out of bounds
            return NULL;
        }

        currentPassenger = &passengers[currentPosition];
    }

    return currentPassenger;
}

void searchPassenger() {
    char code[CODE_LENGTH];

    printf("Enter passenger code: ");
    scanf("%s", code);

    passenger *foundPassenger = findPassengerForCode(code);
    if (foundPassenger == NULL) {
        printf("Passenger not found.\n");
        return;
    }

    printf("   -- Passenger %s\n", foundPassenger->code);
    printf("Name: %s\n", foundPassenger->name);
}