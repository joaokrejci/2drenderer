#ifndef RENDERER_H
#define RENDERER_H

#define bool char
#define true 1
#define false 0

#include <SDL2/SDL.h>
#include "image.h"

typedef struct color {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
} color_t;

typedef struct position {
  int x, y;
} position_t;

typedef struct sprite {
  position_t position;
  int width, height;
  unsigned int *data;
} sprite_t;

typedef struct scene {
  void (*load)(void);
  void (*loop)(void);
  void (*event_handler)(SDL_Event event);
  void (*unload)(void);
} scene_t;

void init();
void start();

sprite_t create_sprite(image_t sprite, bool free_image);
void clear_sprite(sprite_t image);
void draw(sprite_t sprite);

#endif