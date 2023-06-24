#include <stdio.h>
#include <time.h>

#include "renderer.h"
#include "color.h"

SDL_Surface *surface;
SDL_Window *window;

time_t instant;
clock_t frame_instant;
long fps_counter;

void init() {
  SDL_Init(SDL_INIT_VIDEO);

  int width = 1280;
  int height = 720;

  window = SDL_CreateWindow("2d renderer", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height, 0);
  surface = SDL_GetWindowSurface(window);
}

static void draw_primitive(sprite_t sprite, point_t position, unsigned int frame_offset, size_2d_t frame_size) {
    int out_of_bounds =
            position.x < -frame_size.width || position.x > surface->w ||
            position.y < -frame_size.height || position.y > surface->h;

    if (out_of_bounds)
        return;

    unsigned int *pixels = surface->pixels;

    for (int y = 0; y < frame_size.height; y++) {
        int line_pos = position.x + (y + position.y) * surface->w;
        int offset = position.x >= 0 ? 0 : 0 - position.x;
        unsigned int line_length = frame_size.width;

        if(position.x + frame_size.width > surface->w) {
            line_length = surface->w - position.x;
        }

        memcpy(
                pixels + line_pos,
                sprite.data + frame_offset + y * sprite.width + offset,
                line_length * sizeof (int)
                );
    }
}

void draw(sprite_t sprite, point_t position) {
    size_2d_t sprite_size = {sprite.width, sprite.height};
    draw_primitive(sprite, position, 0, sprite_size);
}

void draw_animated(animated_sprite_t animated_sprite, point_t position) {
    int frame_offset = animated_sprite.current_frame * animated_sprite.frame_size.width;
    draw_primitive(animated_sprite.sprite, position, frame_offset, animated_sprite.frame_size);
}

static void fps() {
  if (instant < time(NULL)) {
    printf("\r fps: %ld ", fps_counter);
    fflush(stdout);

    instant = time(NULL);
    fps_counter = 0;
  } else {
    fps_counter++;
  }
}

static double delta() {
    clock_t new_instant = clock();
    double delta_time = ((double)(new_instant - frame_instant))/CLOCKS_PER_SEC;
    frame_instant = new_instant;
    return delta_time;
}

void start(scene_t scene) {
  instant = time(NULL);
  fps_counter = 0;
  frame_instant = clock();

  if (scene.load != NULL) {
    scene.load();
  }

  SDL_Event event;
  while (event.type != SDL_QUIT) {
    int poll_result = SDL_PollEvent(&event);
    if (scene.event_handler != NULL && poll_result) {
      scene.event_handler(event);
    }

    if (scene.loop != NULL) {
      scene.loop(delta());
    }

    SDL_UpdateWindowSurface(window);

    if (scene.flags & FLAG_CLEAR_BACKGROUND) {
      SDL_FillRect(surface, NULL, 0);
    }

    fps();
  }

  if (scene.unload != NULL) {
    scene.unload();
  }

  SDL_Quit();
}