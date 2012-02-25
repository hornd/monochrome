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
static rect** get_rect_in_grid(grid *, U8 *);
static U32 get_total_rectangles_in_grid(grid *);
static bool is_rect_valid(rect *);
static rect* rect_new();
static void rect_free(rect *);

extern U32 get_monochrome_count(grid *g)
{
    U8 i, rectangles_in_grid = 0;
    U32 ret = 0;
    rect **rects = get_rect_in_grid(g, &rectangles_in_grid);
    
/*    printf("Inside get_monochrome_count. Total rect: %d\n", rectangles_in_grid); */

    for(i=0; i<rectangles_in_grid; i++)
    {
        if (rect_is_monochrome(g, rects[i]))
        {
            ret++;
        }
    }

    return ret;
}
 
extern bool rect_is_monochrome(grid *g, rect *r)
{
    color pt0 = get_color(g, r->top_left);
    color pt1 = get_color(g, r->top_right);
    color pt2 = get_color(g, r->bottom_left);
    color pt3 = get_color(g, r->bottom_right);

    char *color_table= "RYGB__";

    if(pt0 == pt1 && pt0 == pt2 && pt0 == pt3)
    {
/*        printf("This is monochrome\n");
        printf("------------------\n");

        printf("%c  %c\n", color_table[pt0], color_table[pt1]);
        printf("%c  %c\n", color_table[pt2], color_table[pt3]);
*/

        return TRUE;
    }
    return FALSE;

/*    return pt0 == pt1 && pt0 == pt2 && pt0 == pt3; */
}


static inline U32 rect_height(rect *r)
{
    return r->bottom_right->y - r->top_left->y;
}

static inline U32 rect_width(rect *r)
{
    return r->bottom_right->x - r->top_left->x;
}

static rect** get_rect_in_grid(grid *g, U8 *count)
{
    U8 start_x, start_y, end_x, end_y;
    U8 rect_idx = 0;
    rect **ret = malloc(sizeof(rect*) * get_total_rectangles_in_grid(g));

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
                    point_set(r->top_right, end_x, start_y);
                    point_set(r->bottom_left, start_x, end_y);

                    if (is_rect_valid(r))  /* is_rect_valid(r) */
                    { 
                        ret[rect_idx++] = r;
                    }
                    else
                    {
                        rect_free(r);
                    }
                }
            }
        }
    }

    *count = rect_idx;
    return ret;
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
    point_free(r->bottom_right);
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
