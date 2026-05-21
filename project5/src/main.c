#include <stdio.h>


#include "db.h"
#include "menu.h"


int main(void)
{
    sqlite3 *db;


    printf("=== Абитуриенты и ВУЗы ===\n");


    db = db_open();


    if (!db)
        return 1;


    db_create_tables(db);


    db_seed(db);


    run_menu(db);


    db_close(db);


    return 0;
}
