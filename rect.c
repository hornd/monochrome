#include <stdlib.h>
#include "rect.h"
#include "grid.h"
#include "util.h"

/************** Debug functions ******************/

#include <stdio.h>
static void dump_point(point *p)
{
    printf("(%d, %d) ", p->x, p->y);
}

static void dump_rectangle(rect *r)
{
    dump_point(r->top_left);
    dump_point(r->top_right);
    printf("\n");
    dump_point(r->bottom_left);
    dump_point(r->bottom_right);
    printf("\n\n");
}

/************** End debug functions *************/


static inline U32 rect_height(rect *);
static inline U32 rect_width(rect *);
static rect** get_rect_in_grid(grid *, int *);
static U32 get_total_rectangles_in_grid(grid *);
static bool is_rect_valid(rect *);
static rect* rect_new();
static void rect_free(rect *);

extern U32 get_monochrome_count(grid *g)
{

}
 
extern bool rect_is_monochrome(grid *g, rect *r)
{
    color pt0 = get_color(g, r->top_left);
    color pt1 = get_color(g, r->top_right);
    color pt2 = get_color(g, r->bottom_left);
    color pt3 = get_color(g, r->bottom_right);

    return pt0 == pt1 && pt0 == pt2 && pt0 == pt3;
}


static inline U32 rect_height(rect *r)
{
    return r->bottom_right->x - r->top_left->x;
}

static inline U32 rect_width(rect *r)
{
    return r->bottom_right->y - r->top_left->y;
}

static rect** get_rect_in_grid(grid *g, int *count)
{
    U8 start_x, start_y, end_x, end_y;
    U32 rect_count = get_total_rectangles_in_grid(g);
    for(start_x = 0; start_x < g->size; start_x++)
    {
        for(start_y = 0; start_y < g->size; start_y++)
        {
            for(end_x = start_x + 1; end_x < g->size; end_x++)
            {
                for(end_y = start_y + 1; end_y < g->size; end_y++)
                {
                    rect *r = rect_new();
                    point_set(r->top_left, start_x, start_y);
                    point_set(r->bottom_right, end_x, end_y);
                    //POINTS ARE WRONG FIX
//                    point_set(r->top_right, start_x, end_y);
                    //                   point_set(r->bottom_left, end_x, start_y);

                    if (is_rect_valid(r))  // is_rect_valid(r)
                    { 
                        
                    }
                    else
                    {
                        rect_free(r);
                    }
                }
            }
        }
    }
}

static bool is_rect_valid(rect *r)
{
    return rect_height(r) >= 1 && rect_width(r) >= 1;
}

static rect* rect_new()
{
    rect *r = malloc(sizeof(rect));
    r->top_left = point_new();
    r->bottom_right = point_new();
    r->top_right = point_new();
    r->bottom_left = point_new();
    return r;
}

static void rect_free(rect *r)
{
    point_free(r->top_left);
    point_free(r->top_right);
    point_free(r->bottom_left);
    point_Free(r->bottom_right);
    free(r);
}

static U32 get_total_rectangles_in_grid(grid *g)
{
    U32 rect_counts[] = 
      {  0,
         1, 
         9,
         36,
         100,
         225,
         441,
         784,
         1296,
         2025,
         3025,
         4356,
         6084,
         8281,
         11025,
         14400 };

    return rect_counts[g->size - 1];
}
