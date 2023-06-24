#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "image.h"
#include "sprite.h"
#include "animated_sprite.h"
#include "../../math/src/geometry.h"

#define FLAG_CLEAR_BACKGROUND 0x01

typedef struct scene {
  void (*load)(void);
  void (*loop)(double delta);
  void (*event_handler)(SDL_Event event);
  void (*unload)(void);

  char flags;
} scene_t;

void init();
void start(scene_t scene);

void draw(sprite_t sprite, point_t position);
void draw_animated(animated_sprite_t animated_sprite, point_t position);

#endif