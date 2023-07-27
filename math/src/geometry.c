#include "geometry.h"
#include <stdlib.h>

int point_compare(point_t p1, point_t p2) {
    return p2.x - p1.x + p2.y - p1.y;
}

point_t point_from_vec2(vec2_t vec2) {
    point_t round_position = {
            (int) floorf(vec2.x),
            (int) floorf(vec2.y)
    };
    return round_position;
}

point_t point(int x, int y) {
    point_t new_point = { x, y };
    return new_point;
}

vec2_t vec2(float x, float y) {
    vec2_t _vec2 = { x, y };
    return _vec2;
}

rect2_t rect(vec2_t position, vec2_t size) {
    rect2_t _rec2 = {position, size};
    return _rec2;
}

vec2_t vec2_from_point(point_t position) {
    vec2_t _vec2 = {
            (float) position.x,
            (float) position.y
    };
    return _vec2;
}

float vec2_modulo(vec2_t vector) {
    return sqrtf(powf(vector.x, 2) + powf(vector.y, 2));
}

vec2_t vec2_normalized(vec2_t vector) {
    float vector_size = vec2_modulo(vector);
    vec2_t new_vector = {
            vector.x / vector_size,
            vector.y / vector_size
    };
    return new_vector;
}

vec2_t vec2_subtraction(vec2_t v1, vec2_t v2) {
    vec2_t new_vector = {
            v1.x - v2.x,
            v1.y - v2.y
    };
    return new_vector;
}

vec2_t vec2_scalar_product(vec2_t vector, double scalar) {
    vec2_t new_vector = {
            vector.x * (float) scalar,
            vector.y * (float) scalar
    };
    return new_vector;
}

int rect2_contains_point(rect2_t rect, vec2_t position) {
    return
        position.x >= rect.position.x
        && position.y >= rect.position.y
        && position.x <= rect.position.x + rect.size.x
        && position.y <= rect.position.y + rect.size.y;
}

static int rect_overlaps_primitive(rect2_t rect1, rect2_t rect2) {
    vec2_t points[4] = {
            {rect2.position.x, rect2.position.y},
            {rect2.position.x + rect2.size.x, rect2.position.y},
            {rect2.position.x + rect2.size.x, rect2.position.y + rect2.size.y},
            {rect2.position.x, rect2.position.y + rect2.size.y}
    };

    return
           rect2_contains_point(rect1, points[0])
        || rect2_contains_point(rect1, points[1])
        || rect2_contains_point(rect1, points[2])
        || rect2_contains_point(rect1, points[3])
    ;
}

int rect2_overlaps(rect2_t rect1, rect2_t rect2) {
    return
           rect_overlaps_primitive(rect1, rect2)
        || rect_overlaps_primitive(rect2, rect1);
}

int compare_float (const void* a, const void* b) {
    return  (int) (*(float*)a - *(float*)b);
}

rect2_t rect2_intersection(rect2_t rect1, rect2_t rect2) {
    if (!rect2_overlaps(rect1, rect2)) {
        return (rect2_t) {0,0,0,0};
    }

    float xs[4] = {rect1.position.x, rect1.position.x + rect1.size.x, rect2.position.x, rect2.position.x + rect2.size.x};
    float ys[4] = {rect1.position.y, rect1.position.y + rect1.size.y, rect2.position.y, rect2.position.y + rect2.size.y};

    qsort(xs, 4, sizeof(float), compare_float);
    qsort(ys, 4, sizeof(float), compare_float);

    vec2_t point1 = vec2(xs[1], ys[1]);
    vec2_t point2 = vec2(xs[2], ys[2]);

    return rect(point1, vec2(point2.x - point1.x, point2.y - point1.y));
}
