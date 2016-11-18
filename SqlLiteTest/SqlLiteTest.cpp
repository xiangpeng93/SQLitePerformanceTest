#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sqlite3.h"

#define INPUTDATA "test.txt"
#define DATABASE "test.db"
#define TABLE "CREATE TABLE IF NOT EXISTS TTC (id INTEGER PRIMARY KEY, DATA TEXT, YEAR TEXT, MONTH TEXT, DAY TEXT, HOUR TEXT, SECOND TEXT, Time TEXT)"
#define BUFFER_SIZE 256

int main()
{
	sqlite3 * db;
	sqlite3_stmt * stmt;
	clock_t cStartClock;
	FILE * pFile;

	int nRetCode;
	int n = 0;
	char sInputBuf[BUFFER_SIZE] = "\0";
	char sSQL[BUFFER_SIZE] = "\0";
	char * sErrMsg = 0;

	/*********************************************/
	/* Open the Database and create the Schema */
	sqlite3_open(DATABASE, &db);
	sqlite3_exec(db, TABLE, NULL, NULL, &sErrMsg);
	sqlite3_exec(db, "PRAGMA synchronous = OFF", NULL, NULL, &sErrMsg);
	sqlite3_exec(db, "PRAGMA journal_mode = MEMORY", NULL, NULL, &sErrMsg);

	sprintf(sSQL, "INSERT INTO TTC VALUES (NULL, @RT, @BR, @VR, @ST, @VI, @DT, @TM)");
	sqlite3_prepare_v2(db, sSQL, BUFFER_SIZE, &stmt, NULL);

	/*********************************************/
	/* Open input file and import into Database*/
	cStartClock = clock();
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &sErrMsg);

	pFile = fopen(INPUTDATA, "r");	
	while (!feof(pFile)) {
		fgets(sInputBuf, BUFFER_SIZE, pFile);  

		/* ACTUAL INSERT WILL GO HERE */
		sqlite3_bind_text(stmt, 1, strtok(sInputBuf, "\t"), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 2, strtok(NULL, "\t"), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 3, strtok(NULL, "\t"), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 4, strtok(NULL, "\t"), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 5, strtok(NULL, "\t"), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 6, strtok(NULL, "\t"), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 7, strtok(NULL, "\t"), -1, SQLITE_TRANSIENT);

		sqlite3_step(stmt);
		sqlite3_clear_bindings(stmt);
		sqlite3_reset(stmt);

		n++;
	}
	fclose(pFile);
	
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &sErrMsg);
	printf("\r\n	插入 %d 记录,共耗时 %4.2f 秒\r\n\n\n", n, (clock() - cStartClock) / (double)CLOCKS_PER_SEC);

	sqlite3_close(db);
	system("pause");
	return 0;
}
