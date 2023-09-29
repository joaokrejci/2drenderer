#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "image.h"
#include "sprite.h"
#include "animated_sprite.h"
#include "../../math/src/geometry.h"

#define FLAG_CLEAR_BACKGROUND 0x01

typedef struct camera {
    vec2_t position;
    unsigned int width;
    unsigned int height;
} camera_t;

typedef struct scene {
  void (*load)(void);
  void (*loop)(double delta);
  void (*event_handler)(SDL_Event event);
  void (*unload)(void);

  char flags;
} scene_t;

void init();
void start(scene_t scene);

camera_t * camera_viewport();
point_t world_to_canvas_position(vec2_t world_position);
vec2_t canvas_to_world_position(point_t canvas_position);

void draw(sprite_t sprite, vec2_t position, int alpha);
void draw_animated(animated_sprite_t * animated_sprite, vec2_t position, int alpha);

#endif