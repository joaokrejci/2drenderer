#ifndef PLATEAU_DOT_H
#define PLATEAU_DOT_H

#include "dynamic_entity.h"

typedef struct dot {
    dynamic_entity_t entity;
    vec2_t destination;
} dot_t;

extern dynamic_entity_t dot_entity_prototype;

dot_t spawn_dot(vec2_t origin, point_t destination);

#endif //PLATEAU_DOT_H
