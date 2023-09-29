#ifndef SPRITE_H
#define SPRITE_H

#include "size_2d.h"
#include "image.h"

typedef struct sprite {
  int width, height;
  unsigned int *data;
} sprite_t;

sprite_t create_sprite(image_t sprite);
void clear_sprite(sprite_t image);
void resize_sprite(sprite_t * sprite, int width, int height);

#endif