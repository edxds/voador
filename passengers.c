//
// Created by Eduardo on 2019-02-23.
//

#include "passengers.h"

passenger passengers[TABLE_SIZE];
int currentPassengerIndex = 0;

void readPassengersTable() {
    // TODO: Move file operations to single header file
    FILE *table = fopen("passengers.ctable", "a+");
    if (table == NULL) {
        printf("ERROR: Could not open passengers.ctable");
        return;
    }

    /*
     * Because the "a+" opening mode sets the file pointer to
     * the end of the file, we need to put it back to the
     * start so that we can read the data in the file properly.
     */
    fseek(table, 0, SEEK_SET);
    fread(&passengers, sizeof(struct passenger), TABLE_SIZE, table);

    /*
     * To calculate the amount of structs saved in the file, we
     * need to move the pointer to the end of the file, and then
     * divide the pointer position by the size of the structs
     * contained in that file
     */
    fseek(table, 0, SEEK_END);
    currentPassengerIndex = (int) (ftell(table) / sizeof(struct passenger));
}

void savePassengerToTable(passenger *passenger) {
    FILE *table = fopen("passengers.ctable", "a+");
    if (table == NULL) {
        printf("ERROR: Could not save passenger.\n");
        return;
    }

    fwrite(passenger, sizeof(struct passenger), 1, table);
    currentPassengerIndex++;
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