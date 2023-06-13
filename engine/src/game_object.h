#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../../2drenderer/src/sprite.h"
#include "geometry.h"

typedef struct game_object {
    sprite_t sprite;
    position_t position;
    unsigned int width;
    unsigned int height;
} game_object_t;

void move_object_by(game_object_t *object, int x, int y);

#endif