#include "game_object.h"

void move_object_by(game_object_t *object, int x, int y) {
    object->position.x += x;
    object->position.y += y;
}