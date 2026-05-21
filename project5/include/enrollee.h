#ifndef ENROLLEE_H
#define ENROLLEE_H

typedef struct {
    int id;

    char surname[64];
    char name[64];
    char patronymic[64];

    char gender[16];
    char nationality[64];

    int birth_year;
    int birth_month;
    int birth_day;

    char city[64];

    int score;
    int vuz_id;

} Enrollee;

#endif
