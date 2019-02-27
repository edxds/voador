//
// Created by Eduardo on 2019-02-23.
//

#include "tables.h"

/**
 * Private function that opens a table file with a given name
 *
 * @param tableName The name of the table to be opened
 *
 * @return A FILE pointer to the table file. NULL if the file
 * doesn't exist or if an error occurred while reading it.
 */
FILE* openTable(char tableName[]) {
    /*
     * Makes accessible file name. If the tableName is "passengers",
     * then fileName will be "passengers.ctable"
     */
    char fileName[80];
    snprintf(fileName, sizeof(fileName), "%s.ctable", tableName);

    FILE *table = fopen(fileName, "a+");
    return table;
}

void readTable(char tableName[], size_t dataSize, void *dataDestination, int *dataIndex) {
    FILE *table = openTable(tableName);
    if (table == NULL) {
        printf("ERROR: Could not open %s.ctable", tableName);
        return;
    }

    /*
     * Because the "a+" opening mode sets the file pointer to
     * the end of the file, we need to put it back to the
     * start so that we can read the data in the file properly.
     */
    fseek(table, 0, SEEK_SET);
    fread(dataDestination, dataSize, TABLE_SIZE, table);

    /*
     * To calculate the amount of structs saved in the file, we
     * need to move the pointer to the end of the file, and then
     * divide the pointer position by the size of the structs
     * contained in that file
     */
    fseek(table, 0, SEEK_END);
    (*dataIndex) = (int) (ftell(table) / dataSize);

    // Prevents memory leaks and commits changes to file
    fclose(table);
}

void saveToTable(char tableName[], size_t dataSize, void *data, int *dataIndex) {
    FILE *table = openTable(tableName);
    if (table == NULL) {
        printf("ERROR: Could not save data to %s.ctable", tableName);
        return;
    }

    fwrite(data, dataSize, 1, table);
    (*dataIndex)++;

    // Prevents memory leaks and commits changes to file
    fclose(table);
}