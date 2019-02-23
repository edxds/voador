#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "passengers.h"
#include "flights.h"
#include "relations.h"
#include "ui.h"

int main() {
    readPassengersTable();
    readFlightsTable();
    readRelationsTable();

    runUiLoop();
}