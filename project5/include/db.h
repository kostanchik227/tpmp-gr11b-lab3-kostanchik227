#ifndef DB_H
#define DB_H

#include <sqlite3.h>

sqlite3 *db_open(void);

void db_close(sqlite3 *db);

void db_create_tables(sqlite3 *db);

void db_seed(sqlite3 *db);

void db_select_all(sqlite3 *db);

void db_select_score_225(sqlite3 *db);

void db_count_250(sqlite3 *db);

void db_sum_male(sqlite3 *db);

void db_max_min(sqlite3 *db);

void db_inner_join(sqlite3 *db);

#endif
