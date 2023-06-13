#include <stdio.h>
#include <time.h>

#include "renderer.h"
#include "color.h"

SDL_Surface *surface;
SDL_Window *window;

time_t instant;
long fps_counter;

void init() {
  SDL_Init(SDL_INIT_VIDEO);

  int width = 1280;
  int height = 720;

  window = SDL_CreateWindow("2d renderer", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height, 0);
  surface = SDL_GetWindowSurface(window);
}

void draw(sprite_t sprite, position_t position) {
  int out_of_bounds =
      position.x < -sprite.width || position.x > surface->w ||
      position.y < -sprite.height || position.y > surface->h;

  if (out_of_bounds)
    return;

  unsigned int *pixels = surface->pixels;

  for (int y = 0; y < sprite.height; y++) {
      int line_pos = position.x + (y + position.y) * surface->w;
      int offset = position.x >= 0 ? 0 : 0 - position.x;
      int line_length = sprite.width;

      if(position.x + sprite.width > surface->w) {
          line_length = surface->w - position.x;
      }

      memcpy(pixels + line_pos, sprite.data + y * sprite.width + offset, line_length * sizeof (int));
  }
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

void start(scene_t scene) {
  instant = time(NULL);
  fps_counter = 0;

  if (scene.load != NULL) {
    scene.load();
  }

  SDL_Event event;
  while (event.type != SDL_QUIT) {
    SDL_PollEvent(&event);
    if (scene.event_handler != NULL) {
      scene.event_handler(event);
    }

    if (scene.loop != NULL) {
      scene.loop();
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