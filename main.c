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

int main(int argc, char ** argv)
{
    U8 goal_size;
    grid *g;
    if (argc != 2)
    {
        printf("Usage: monochrome <size>\n");
        exit(EXIT_FAILURE);
    }

    goal_size = atoi(argv[1]);
    g = grid_new(goal_size);
    grid_init(g);

    while(get_monochrome_count(g) != 0)
    {
        grid_free(g);
        g = grid_new(goal_size);
        grid_init(g);
    } 

    print_solution(g);

    return 0;

}
