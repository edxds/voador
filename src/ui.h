//
// Created by Eduardo on 2019-02-23.
//

#include "passengers.h"
#include "flights.h"
#include "relations.h"

#ifndef VOADOR_UI_H
#define VOADOR_UI_H

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
void flushAndWait();

/**
 * Function that runs the function associated
 * with the menu option that the user choose.
 *
 * @param option User's menu option
 */
void handleMenuOption(int option);

/**
 * Function that runs as long as the user doesn't input -1.
 * Calls handleMenuOption after user inputs option.
 */
void runUiLoop();

#endif //VOADOR_UI_H
