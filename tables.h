//
// Created by Eduardo on 2019-02-23.
//

#include <stdio.h>
#include <stdlib.h>

#ifndef VOADOR_TABLES_H
#define VOADOR_TABLES_H

#define TABLE_SIZE 300

/**
 * Opens a specific table and reads the data from the file to the
 * passed array. Also sets the passed data index according to the
 * number of structs saved in the file.
 *
 * @param tableName The name of the table to be read
 * @param dataSize The size of the struct that is stored in the file
 * @param dataDestination Pointer to the array in which the structs are stored
 * @param dataIndex Pointer to the variable that holds the current table index
 */
void readTable(char tableName[], size_t dataSize, void *dataDestination, int *dataIndex);

/**
 * Opens the table file with the name passed and appends
 * the passed struct to end of the .ctable file. Increments
 * passed array index if save was successful.
 *
 * @param tableName The name of the table to be saved to
 * @param dataSize The size of the struct that is stored in the file
 * @param data Pointer to the data that will be saved to the file
 * @param dataIndex Pointer to the variable that holds the current table index
 */
void saveToTable(char tableName[], size_t dataSize, void *data, int *dataIndex);

#endif //VOADOR_TABLES_H
