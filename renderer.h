#ifndef RENDERER_H
#define RENDERER_H

#define bool char
#define true 1
#define false 0

#include <SDL2/SDL.h>
#include "image.h"
#include "sprite.h"

typedef struct scene {
  void (*load)(void);
  void (*loop)(void);
  void (*event_handler)(SDL_Event event);
  void (*unload)(void);
} scene_t;

void init();
void start(scene_t scene);

void draw(sprite_t sprite);

#endif