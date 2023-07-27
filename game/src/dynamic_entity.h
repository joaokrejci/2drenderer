//
// Created by joao on 24/06/23.
//

#ifndef PLATEAU_DYNAMIC_ENTITY_H
#define PLATEAU_DYNAMIC_ENTITY_H

#include "../../math/src/geometry.h"
#include "../../2drenderer/src/sprite.h"
#include "../../2drenderer/src/animated_sprite.h"

typedef struct dynamic_entity {
    animated_sprite_t sprite;
    vec2_t position;
    vec2_t velocity;
} dynamic_entity_t;

void move_dynamic_entity(dynamic_entity_t * entity, double delta);
void move_dynamic_entity_to_destination(dynamic_entity_t * entity, vec2_t destination, double delta);

#endif //PLATEAU_DYNAMIC_ENTITY_H
