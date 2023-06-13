#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct rectangle {
    int x, y;
    int w, h;
} rectangle_t;

typedef struct vec2 {
    int x, y;
} vec2_t;

int is_inside(vec2_t point, rectangle_t box);

#endif