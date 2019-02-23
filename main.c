#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CODE_LENGTH     6
#define TABLE_SIZE      300

#define UI_IDLE                     0
#define UI_REGISTER_PASSENGER       1
#define UI_REGISTER_FLIGHT          2
#define UI_SEARCH_PASSENGER         3
#define UI_SEARCH_FLIGHT            4
#define UI_ASSIGN_PASSENGER         5
#define UI_CHECK_PASSENGER_FLIGHTS  6
#define UI_CHECK_FLIGHT_PASSENGERS  7
#define UI_EXIT                     -1

typedef struct passenger {
    char code[CODE_LENGTH];
    char name[25];
} passenger;

typedef struct flight {
    char code[CODE_LENGTH];
    char origin[3];
    char destination[3];
} flight;

typedef struct relation {
    char code_passenger[CODE_LENGTH];
    char code_flight[CODE_LENGTH];
} relation;

passenger passengers[TABLE_SIZE];
flight flights[TABLE_SIZE];
relation relations[TABLE_SIZE];

int currentPassengerIndex = 0;
int currentFlightIndex = 0;
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
 * Opens passengers table and reads the data from the file to the
 * passengers array. Also sets the passenger index according to the
 * number of passengers saved in the file.
 */
void readPassengersTable() {
    FILE *table = fopen("passengers.ctable", "a+");
    if (table == NULL) {
        printf("ERROR: Could not open passengers.ctable");
        return;
    }

    fseek(table, 0, SEEK_SET);
    fread(&passengers, sizeof(struct passenger), TABLE_SIZE, table);

    fseek(table, 0, SEEK_END);
    currentPassengerIndex = (int) (ftell(table) / sizeof(struct passenger));
}

/**
 * Appends passenger struct to end of passengers.ctable file.
 *
 * @param passenger Pointer to the passenger struct that will be saved.
 */
void savePassengerToTable(passenger *passenger) {
    FILE *table = fopen("passengers.ctable", "a+");
    if (table == NULL) {
        printf("ERROR: Could not save passenger.\n");
    } else {
        fwrite(passenger, sizeof(struct passenger), 1, table);
    }
}

/**
 * Function that takes user input, registers a new passenger,
 * and saves it to the passengers table.
 * Increments passenger array index.
 */
void registerPassenger() {
    printf("   -- Register passenger\n");

    printf("Name: ");
    scanf("%s", passengers[currentPassengerIndex].name);

    printf("Code: ");
    scanf("%s", passengers[currentPassengerIndex].code);

    savePassengerToTable(&passengers[currentPassengerIndex]);
    currentPassengerIndex++;

    flushAndWait();
}

/**
 * Finds a passenger with the matching code.
 *
 * @param code The code of the passenger that you want to find.

 * @return A pointer to the found passenger. NULL if the
 * passenger isn't found
 */
passenger* findPassengerForCode(char code[]) {
    int currentPosition = 0;
    passenger *currentPassenger = &passengers[currentPosition];

    // While the current passenger's code
    // isn't equal to the code requested
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

/**
 * Asks user for a passenger code and searches a passenger with
 * the corresponding code and shows its information.
 */
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

/**
 * Opens flights table and reads the data from the file to the
 * flights array. Also sets the flight index according to the
 * number of flights saved in the file.
 */
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

/**
 * Appends flight struct to end of flights.ctable file.
 *
 * @param flight Pointer to the flight struct that will be saved.
 */
void saveFlightToTable(flight *flight) {
    FILE *table = fopen("flights.ctable", "a+");
    if (table == NULL) {
        printf("ERROR: Could not save flight.\n");
    } else {
        fwrite(flight, sizeof(struct flight), 1, table);
    }
}

/**
 * Function that takes user input, registers a new flight,
 * and saves it to the flights table.
 * Increments flight array index.
 */
void registerFlight() {
    printf("   -- Register flight\n");

    printf("Code: ");
    scanf("%s", flights[currentFlightIndex].code);

    printf("Origin: ");
    scanf("%s", flights[currentFlightIndex].origin);

    printf("Destination: ");
    scanf("%s", flights[currentFlightIndex].destination);

    saveFlightToTable(&flights[currentFlightIndex]);
    currentFlightIndex++;

    flushAndWait();
}

/**
 * Finds a flight with the matching code.
 *
 * @param code The code of the flight that you want to find.

 * @return A pointer to the found flight. NULL if the
 * flight isn't found
 */
flight* findFlightForCode(char code[]) {
    int currentPosition = 0;
    flight *currentFlight = &flights[currentPosition];

    // While the current flight's code isn't equal
    // to the code requested
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

/**
 * Asks user for a flight code and searches a flight with
 * the corresponding code and shows its information.
 */
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
            break;
        case UI_REGISTER_FLIGHT:
            printf("\n");
            registerFlight();
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