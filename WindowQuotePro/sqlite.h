


typedef int (*callbk)(void*, int, char**, char**);

int sqlite_open(const char *path);

int sqlite_run_query(const char *query);

int sqlite_run_select(const char* query, callbk func, void* reply);

static int empty_callback(void *NotUsed, int argc, char **argv, char **azColName);

int sqlite_close();

