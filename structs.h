//
// Created by Eduardo on 2019-02-23.
//

#ifndef VOADOR_STRUCTS_H
#define VOADOR_STRUCTS_H

#define CODE_LENGTH 6

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

#endif //VOADOR_STRUCTS_H
