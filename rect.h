#ifndef __RECT_H
#define __RECT_H

#include "grid.h"
#include "util.h"

typedef struct
{
    point *top_left;
    point *top_right;
    point *bottom_left;
    point *bottom_right;
} rect;

extern U32 get_monochrome_count(grid *);

extern bool rect_is_monochrome(grid *g, rect *r);

extern bool is_rectangle_monochrome(grid *, rect);

#endif
