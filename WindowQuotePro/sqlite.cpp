#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"
#include "sqlite.h"

sqlite3 *db;

int aaa() 
{
    return 0;
}


int sqlite_open(const char *path)
{
    char *zErrMsg = 0;
    
    int rc = sqlite3_open(path, &db);

    if( rc )
    {
        sqlite3_close(db);
        return(1);
    }

    return rc;
}

int sqlite_run(const char *query, callbk func, void * reply)
{
    char *zErrMsg = 0;
    
    int rc = sqlite3_exec(db, query, func, reply, &zErrMsg);

    if( rc != SQLITE_OK )
        sqlite3_free(zErrMsg);

    return rc;
}

int sqlite_run_select(const char* query, callbk func, void* reply)
{
    return sqlite_run(query, func, reply);
}

int sqlite_run_query(const char *query)
{
    return sqlite_run(query, empty_callback, 0);
}

int sqlite_close()
{
    sqlite3_close(db);

    return 0;
}



static int empty_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    return 0;
}
