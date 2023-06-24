#include "geometry.h"

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

vec2_t vec2_from_point(point_t position) {
    vec2_t vec2 = {
            (float) position.x,
            (float) position.y
    };
    return vec2;
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
