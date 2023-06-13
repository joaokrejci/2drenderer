#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "image.h"
#include "sprite.h"

#define FLAG_CLEAR_BACKGROUND 0x01

typedef struct scene {
  void (*load)(void);
  void (*loop)(void);
  void (*event_handler)(SDL_Event event);
  void (*unload)(void);

  char flags;
} scene_t;

void init();
void start(scene_t scene);

void draw(sprite_t sprite, position_t position);

#endif