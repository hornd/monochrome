#ifndef __GRID_H
#define __GRID_H

typedef enum
{
    red,
    yellow,
    green,
    blue,
    num_colors,
    open
} color; 

typedef struct
{
    int x, y;
} point;

typedef color** grid_ptr;

typedef struct
{
    grid_ptr table;
    int size;
} grid;

extern color get_color(grid *, point *);

extern void grid_dump(grid *);

extern grid* grid_new(int);

extern void grid_free(grid *);

extern void grid_init(grid *);

extern void grid_expand(grid *, int);

#endif
