//
// Created by Eduardo on 2019-02-23.
//

#include "relations.h"

relation relations[TABLE_SIZE];
int currentRelationIndex = 0;

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

void saveRelationToTable(relation *relation) {
    FILE *table = fopen("relations.ctable", "a+");
    if (table == NULL) {
        printf("ERROR: Could not save assignment.\n");
        return;
    }

    fwrite(relation, sizeof(struct relation), 1, table);
    currentRelationIndex++;
}

int alreadyHasRelation(char passengerCode[], char flightCode[]) {
    int i;
    for (i = 0; i <= currentRelationIndex; i++) {
        relation currentRelation = relations[i];

        // If the codes in the current relation match the passed codes
        if (strcmp(currentRelation.code_passenger, passengerCode) == 0
            && strcmp(currentRelation.code_flight, flightCode) == 0) {
            return 1;
        }
    }

    return 0;
}

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

    printf("Assigned passenger %s to flight %s.\n", passengerCode, flightCode);
}

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
    int i;

    for (i = 0; i <= currentRelationIndex; i++) {
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
    int i;

    for (i = 0; i <= currentRelationIndex; i++) {
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