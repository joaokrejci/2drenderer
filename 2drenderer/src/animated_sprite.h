#ifndef PLATEAU_ANIMATED_SPRITE_H
#define PLATEAU_ANIMATED_SPRITE_H

#include "sprite.h"

typedef struct animated_sprite {
    size_2d_t frame_size;
    sprite_t sprite;
    unsigned int current_frame;
    unsigned int frames;
    unsigned int fps;
} animated_sprite_t;

animated_sprite_t create_animated_sprite(sprite_t sprite, int frame_width, int frame_height, unsigned int fps);
void advance_frame(animated_sprite_t * animated_sprite);

#endif //PLATEAU_ANIMATED_SPRITE_H
