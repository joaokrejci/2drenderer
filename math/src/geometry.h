#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "math.h"

typedef struct vec2 {
    float x, y;
} vec2_t;

typedef struct point {
    int x, y;
} point_t;

typedef struct rect2 {
    vec2_t position;
    vec2_t size;
} rect2_t;

point_t point(int x, int y);
vec2_t vec2(float x, float y);
rect2_t rect(vec2_t position, vec2_t size);
int point_compare(point_t p1, point_t p2);
point_t point_from_vec2(vec2_t vec2);
vec2_t vec2_from_point(point_t position);
float vec2_modulo(vec2_t vector);
vec2_t vec2_normalized(vec2_t vector);
vec2_t vec2_subtraction(vec2_t v1, vec2_t v2);
vec2_t vec2_scalar_product(vec2_t vector, double scalar);
int rect2_contains_point(rect2_t rect, vec2_t position);
int rect2_overlaps(rect2_t rect1, rect2_t rect2);
rect2_t rect2_intersection(rect2_t rect1, rect2_t rect2);

#endif