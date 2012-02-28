#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "grid.h"
#include "rect.h"
#include "util.h"

#define MAX_GRID_TRIVIAL 3

void print_solution(grid *g)
{
    printf("*******************************\n");
    printf("Solution for size: %d\n", g->size);
    printf("*******************************\n");
    grid_dump(g);
}

/*static void go(uint8_t goal_size)
{
        grid *g = grid_trivial(MAX_GRID_TRIVIAL); 
}*/


int main(int argc, char ** argv)
{
    U8 x, y;
    char *color_table = "RYGB__";

    U8 debug_count = 0;

    uint8_t goal_size;
    grid *g;
    if (argc != 2)
    {
        printf("Usage: monochrome <size>\n");
        exit(EXIT_FAILURE);
    }

    goal_size = atoi(argv[1]);

    g = grid_new(goal_size);

    grid_init(g);


    get_monochrome_count(g);

    while(get_monochrome_count(g) != 0)
    {
        grid_free(g);
        g = grid_new(goal_size);
        grid_init(g);
    } 


    grid_dump(g);

    return 0;

}

/*    if (goal_size <= MAX_GRID_TRIVIAL)
    {
        ( print_solution(grid_trivial(goal_size)); 
   }
    else
    {
        go(goal_size);
    }

    return 0;
} */
