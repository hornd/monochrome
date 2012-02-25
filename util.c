#include <stdlib.h>
#include "util.h"

extern point* point_new()
{
    point *p = malloc(sizeof(point));
    return p;
}

extern void point_free(point *p)
{
    free(p);
}

extern void point_set(point *p, U8 x, U8 y)
{
    p->x = x;
    p->y = y;
}
