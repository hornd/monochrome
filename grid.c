#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "grid.h"

static char *color_table = "RYGB__";

extern color get_color(grid *g, point *p)
{
    return g->table[p->x][p->y];
}

extern void grid_dump(grid *g)
{
    int x, y, size = g->size;
    for(x=0; x<size; x++)
    {
        for(y=0; y<size; y++)
        {
            printf("%c ", color_table[g->table[x][y]]);
        }
        printf("\n");
    }
    printf("\n");
}

extern grid* grid_new(uint8_t size)
{
    int i;
    grid *g = malloc(sizeof(grid));

    g->table = malloc(sizeof(color *) * size);
    for(i=0; i<size; i++)
    {
        g->table[i] = malloc(sizeof(color) * size);
    }
    g->size = size;
    return g;
}

extern void grid_free(grid *g)
{
    int i;
    for(i=0; i<g->size; i++)
    {
        free(g->table[i]);
    }
    free(g->table);
    free(g);
}

extern void grid_init(grid *g)
{
    static bool needSeed = TRUE;
    int x, y;

    if(needSeed)
    {
        srand((unsigned int)time(NULL));
        needSeed = FALSE;
    }

    for(x=0; x<g->size; x++)
    {
        for(y=0; y<g->size; y++)
        {
            color rndcolor = (color)(rand() % num_colors);
            ((g->table)[x][y]) = rndcolor;
        }
    }
   
}

extern void grid_expand(grid *g, int new_size)
{

}





