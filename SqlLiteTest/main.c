#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sqlite3.h"

#define INPUTDATA "test.txt"
#define DATABASE "test.sqlite"
#define TABLE "CREATE TABLE IF NOT EXISTS TTC (id INTEGER PRIMARY KEY, Route_ID TEXT, Branch_Code TEXT, Version INTEGER, Stop INTEGER, Vehicle_Index INTEGER, Day Integer, Time TEXT)"
#define BUFFER_SIZE 256

int main()
{
    printf("test start\n");
    sqlite3 * db;
    sqlite3_stmt * stmt;
    char * sErrMsg = 0;
    char * tail = 0;
    int nRetCode;
    int n = 0;

    clock_t cStartClock;

    FILE * pFile;
    char sInputBuf [BUFFER_SIZE] = "\0";

    char * sRT = 0;  /* Route */
    char * sBR = 0;  /* Branch */
    char * sVR = 0;  /* Version */
    char * sST = 0;  /* Stop Number */
    char * sVI = 0;  /* Vehicle */
    char * sDT = 0;  /* Date */
    char * sTM = 0;  /* Time */

    char sSQL [BUFFER_SIZE] = "\0";

    /*********************************************/
    /* Open the Database and create the Schema */
    sqlite3_open(DATABASE, &db);
    sqlite3_exec(db, TABLE, NULL, NULL, &sErrMsg);

    /*********************************************/
    /* Open input file and import into Database*/
    cStartClock = clock();

    pFile = fopen (INPUTDATA,"r");
    while (!feof(pFile)) {

        fgets (sInputBuf, BUFFER_SIZE, pFile);

        sRT = strtok (sInputBuf, "\t");     /* Get Route */
        sBR = strtok (NULL, "\t");            /* Get Branch */
        sVR = strtok (NULL, "\t");            /* Get Version */
        sST = strtok (NULL, "\t");            /* Get Stop Number */
        sVI = strtok (NULL, "\t");            /* Get Vehicle */
        sDT = strtok (NULL, "\t");            /* Get Date */
        sTM = strtok (NULL, "\t");            /* Get Time */

        /* ACTUAL INSERT WILL GO HERE */

        n++;
    }
    fclose (pFile);

    printf("Imported %d records in %4.2f seconds\n", n, (clock() - cStartClock) / (double)CLOCKS_PER_SEC);

    sqlite3_close(db);
    return 0;
}
