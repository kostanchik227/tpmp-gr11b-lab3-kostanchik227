#include <stdio.h>
#include <string.h>


#include "menu.h"
#include "db.h"
#include "enrollee.h"


void run_menu(sqlite3 *db)
{
    int choice;
    int id;


    char pattern[64];


    Enrollee e;


    do {


        printf("\n========== MENU ==========\n");


        printf("1. Show all\n");
        printf("2. Find by id\n");
        printf("3. Find by surname\n");
        printf("4. Score > 225\n");
        printf("5. Count score > 250\n");
        printf("6. Sum male scores\n");
        printf("7. Max and min score\n");
        printf("8. Join with VUZ\n");
        printf("9. Insert enrollee\n");
        printf("10. Delete enrollee\n");
        printf("11. AUTOCOMMIT demo\n");
        printf("12. TRANSACTION demo\n");
        printf("0. Exit\n");


        printf("Choice: ");
        scanf("%d", &choice);


        switch (choice) {


        case 1:
            db_select_all(db);
            break;


        case 2:


            printf("Enter id: ");
            scanf("%d", &id);


            db_select_by_id(db, id);


            break;


        case 3:


            printf("Enter surname pattern: ");
            scanf("%63s", pattern);


            db_select_by_surname(db, pattern);


            break;


        case 4:
            db_select_score_225(db);
            break;


        case 5:
            db_count_250(db);
            break;


        case 6:
            db_sum_male(db);
            break;


        case 7:
            db_max_min(db);
            break;


        case 8:
            db_join_vuz(db);
            break;


        case 9:


            memset(&e, 0, sizeof(e));


            printf("Surname: ");
            scanf("%63s", e.surname);


            printf("Name: ");
            scanf("%63s", e.name);


            printf("Patronymic: ");
            scanf("%63s", e.patronymic);


            printf("Gender: ");
            scanf("%15s", e.gender);


            printf("Nationality: ");
            scanf("%63s", e.nationality);


            printf("Birth year: ");
            scanf("%d", &e.birth_year);


            printf("Birth month: ");
            scanf("%d", &e.birth_month);


            printf("Birth day: ");
            scanf("%d", &e.birth_day);


            printf("Score: ");
            scanf("%d", &e.score);


            printf("VUZ id: ");
            scanf("%d", &e.vuz_id);


            db_insert(db, &e);


            break;


        case 10:


            printf("Enter id: ");
            scanf("%d", &id);


            db_delete(db, id);


            break;


        case 11:
            db_demo_autocommit(db);
            break;


        case 12:
            db_demo_transaction(db);
            break;


        case 0:
            printf("Exit\n");
            break;


        default:
            printf("Wrong choice\n");
        }


    } while (choice != 0);
}
