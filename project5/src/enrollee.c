#include <stdio.h>
#include "enrollee.h"


void print_enrollee(const Enrollee *e)
{
    printf(
        "[%d] %s %s %s | score=%d\n",
        e->id,
        e->surname,
        e->name,
        e->patronymic,
        e->score
    );
}
