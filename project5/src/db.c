#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "db.h"


sqlite3 *db_open(void)
{
    sqlite3 *db;


    if (sqlite3_open(DB_FILE, &db) != SQLITE_OK) {


        printf("Database open error\n");


        return NULL;
    }


    printf("Database opened\n");


    return db;
}


void db_close(sqlite3 *db)
{
    sqlite3_close(db);
}


int db_create_tables(sqlite3 *db)
{
    char *err = NULL;


    const char *sql =


        "CREATE TABLE IF NOT EXISTS vuz ("
        "id INTEGER PRIMARY KEY,"
        "vuz_name TEXT,"
        "vuz_description TEXT);"


        "CREATE TABLE IF NOT EXISTS enrollee ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "surname TEXT,"
        "name TEXT,"
        "patronymic TEXT,"
        "gender TEXT,"
        "nationality TEXT,"
        "birth_year INTEGER,"
        "birth_month INTEGER,"
        "birth_day INTEGER,"
        "score INTEGER,"
        "vuz_id INTEGER,"
        "photo BLOB);";


    if (sqlite3_exec(db, sql, NULL, NULL, &err) != SQLITE_OK) {


        printf("CREATE ERROR: %s\n", err);


        sqlite3_free(err);


        return -1;
    }


    return 0;
}


int db_seed(sqlite3 *db)
{
    sqlite3_exec(
        db,


        "INSERT OR IGNORE INTO vuz VALUES"
        "(1,'BSU','University'),"
        "(2,'BNTU','Technical'),"
        "(3,'BSTU','Technology');",


        NULL,
        NULL,
        NULL
    );


    sqlite3_exec(
        db,


        "INSERT OR IGNORE INTO enrollee VALUES"
        "(1,'Ivanov','Ivan','Ivanovich','male','Belarusian',2005,5,15,260,1,NULL),"
        "(2,'Petrov','Petr','Petrovich','male','Russian',2004,3,20,240,2,NULL),"
        "(3,'Sidorova','Anna','Sergeevna','female','Belarusian',2005,7,12,280,3,NULL),"
        "(4,'Kozlov','Alex','Ivanovich','male','Belarusian',2003,1,10,220,1,NULL);",


        NULL,
        NULL,
        NULL
    );


    return 0;
}


int db_select_all(sqlite3 *db)
{
    sqlite3_stmt *stmt;


    sqlite3_prepare_v2(
        db,


        "SELECT id,surname,name,score FROM enrollee;",


        -1,
        &stmt,
        NULL
    );


    printf("\nALL ENROLLEES:\n");


    while (sqlite3_step(stmt) == SQLITE_ROW) {


        printf(
            "[%d] %s %s score=%d\n",


            sqlite3_column_int(stmt, 0),


            sqlite3_column_text(stmt, 1),


            sqlite3_column_text(stmt, 2),


            sqlite3_column_int(stmt, 3)
        );
    }


    sqlite3_finalize(stmt);


    return 0;
}


int db_select_by_id(sqlite3 *db, int id)
{
    sqlite3_stmt *stmt;


    sqlite3_prepare_v2(
        db,


        "SELECT surname,name,score FROM enrollee WHERE id=?;",


        -1,
        &stmt,
        NULL
    );


    sqlite3_bind_int(stmt, 1, id);


    if (sqlite3_step(stmt) == SQLITE_ROW) {


        printf(
            "%s %s score=%d\n",


            sqlite3_column_text(stmt, 0),


            sqlite3_column_text(stmt, 1),


            sqlite3_column_int(stmt, 2)
        );
    }
    else {


        printf("Not found\n");
    }


    sqlite3_finalize(stmt);


    return 0;
}


int db_select_by_surname(sqlite3 *db, const char *pattern)
{
    sqlite3_stmt *stmt;


    sqlite3_prepare_v2(
        db,


        "SELECT surname,name FROM enrollee WHERE surname LIKE ?;",


        -1,
        &stmt,
        NULL
    );


    sqlite3_bind_text(stmt, 1, pattern, -1, SQLITE_STATIC);


    while (sqlite3_step(stmt) == SQLITE_ROW) {


        printf(
            "%s %s\n",


            sqlite3_column_text(stmt, 0),


            sqlite3_column_text(stmt, 1)
        );
    }


    sqlite3_finalize(stmt);


    return 0;
}


int db_select_score_225(sqlite3 *db)
{
    sqlite3_stmt *stmt;


    sqlite3_prepare_v2(
        db,


        "SELECT surname,name,score FROM enrollee WHERE score > 225;",


        -1,
        &stmt,
        NULL
    );


    printf("\nSCORE > 225:\n");


    while (sqlite3_step(stmt) == SQLITE_ROW) {


        printf(
            "%s %s score=%d\n",


            sqlite3_column_text(stmt, 0),


            sqlite3_column_text(stmt, 1),


            sqlite3_column_int(stmt, 2)
        );
    }


    sqlite3_finalize(stmt);


    return 0;
}


int db_count_250(sqlite3 *db)
{
    sqlite3_stmt *stmt;


    sqlite3_prepare_v2(
        db,


        "SELECT COUNT(*) FROM enrollee WHERE score > 250;",


        -1,
        &stmt,
        NULL
    );


    if (sqlite3_step(stmt) == SQLITE_ROW) {


        printf(
            "COUNT > 250 = %d\n",


            sqlite3_column_int(stmt, 0)
        );
    }


    sqlite3_finalize(stmt);


    return 0;
}


int db_sum_male(sqlite3 *db)
{
    sqlite3_stmt *stmt;


    sqlite3_prepare_v2(
        db,


        "SELECT SUM(score) FROM enrollee WHERE gender='male';",


        -1,
        &stmt,
        NULL
    );


    if (sqlite3_step(stmt) == SQLITE_ROW) {


        printf(
            "SUM male = %d\n",


            sqlite3_column_int(stmt, 0)
        );
    }


    sqlite3_finalize(stmt);


    return 0;
}


int db_max_min(sqlite3 *db)
{
    sqlite3_stmt *stmt;


    sqlite3_prepare_v2(
        db,


        "SELECT MAX(score), MIN(score) FROM enrollee;",


        -1,
        &stmt,
        NULL
    );


    if (sqlite3_step(stmt) == SQLITE_ROW) {


        printf(
            "MAX=%d MIN=%d\n",


            sqlite3_column_int(stmt, 0),


            sqlite3_column_int(stmt, 1)
        );
    }


    sqlite3_finalize(stmt);


    return 0;
}


int db_join_vuz(sqlite3 *db)
{
    sqlite3_stmt *stmt;


    sqlite3_prepare_v2(
        db,


        "SELECT e.surname,e.name,v.vuz_name "
        "FROM enrollee e "
        "INNER JOIN vuz v ON e.vuz_id=v.id "
        "WHERE v.id=3;",


        -1,
        &stmt,
        NULL
    );


    printf("\nJOIN RESULT:\n");


    while (sqlite3_step(stmt) == SQLITE_ROW) {


        printf(
            "%s %s -> %s\n",


            sqlite3_column_text(stmt, 0),


            sqlite3_column_text(stmt, 1),


            sqlite3_column_text(stmt, 2)
        );
    }


    sqlite3_finalize(stmt);


    return 0;
}


int db_insert(sqlite3 *db, const Enrollee *e)
{
    sqlite3_stmt *stmt;


    sqlite3_prepare_v2(
        db,


        "INSERT INTO enrollee "
        "(surname,name,patronymic,gender,nationality,"
        "birth_year,birth_month,birth_day,score,vuz_id)"
        "VALUES(?,?,?,?,?,?,?,?,?,?);",


        -1,
        &stmt,
        NULL
    );


    sqlite3_bind_text(stmt, 1, e->surname, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, e->name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, e->patronymic, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, e->gender, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, e->nationality, -1, SQLITE_STATIC);


    sqlite3_bind_int(stmt, 6, e->birth_year);
    sqlite3_bind_int(stmt, 7, e->birth_month);
    sqlite3_bind_int(stmt, 8, e->birth_day);


    sqlite3_bind_int(stmt, 9, e->score);


    sqlite3_bind_int(stmt, 10, e->vuz_id);


    sqlite3_step(stmt);


    sqlite3_finalize(stmt);


    printf("Inserted\n");


    return 0;
}


int db_delete(sqlite3 *db, int id)
{
    sqlite3_stmt *stmt;


    sqlite3_prepare_v2(
        db,


        "DELETE FROM enrollee WHERE id=?;",


        -1,
        &stmt,
        NULL
    );


    sqlite3_bind_int(stmt, 1, id);


    sqlite3_step(stmt);


    sqlite3_finalize(stmt);


    printf("Deleted\n");


    return 0;
}


void db_demo_autocommit(sqlite3 *db)
{
    int i;
    char sql[256];


    printf("AUTOCOMMIT DEMO\n");


    for (i = 100; i < 110; i++) {


        sprintf(
            sql,


            "INSERT INTO enrollee "
            "(id,surname,name,score,vuz_id)"
            "VALUES(%d,'Test','Auto',200,1);",


            i
        );


        sqlite3_exec(db, sql, NULL, NULL, NULL);
    }


    sqlite3_exec(
        db,
        "DELETE FROM enrollee WHERE id>=100;",
        NULL,
        NULL,
        NULL
    );
}


void db_demo_transaction(sqlite3 *db)
{
    int i;
    char sql[256];


    printf("TRANSACTION DEMO\n");


    sqlite3_exec(db, "BEGIN;", NULL, NULL, NULL);


    for (i = 200; i < 210; i++) {


        sprintf(
            sql,


            "INSERT INTO enrollee "
            "(id,surname,name,score,vuz_id)"
            "VALUES(%d,'Test','Trans',200,1);",


            i
        );


        sqlite3_exec(db, sql, NULL, NULL, NULL);
    }


    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);


    sqlite3_exec(
        db,
        "DELETE FROM enrollee WHERE id>=200;",
        NULL,
        NULL,
        NULL
    );
}
