#include "renderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static SDL_Surface *surface;
static SDL_Window *window;

time_t instant;
long fps_counter;

static unsigned int map_rgba(color_t *color) {
  return SDL_MapRGBA(surface->format, color->r, color->g, color->b, color->a);
}

void init() {
  SDL_Init(SDL_INIT_VIDEO);

  int width = 1280;
  int height = 720;

  window = SDL_CreateWindow("2d renderer", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height, 0);
  surface = SDL_GetWindowSurface(window);
}

sprite_t create_sprite(image_t image, bool free_image) {
  sprite_t sprite;
  sprite.width = image.width;
  sprite.height = image.height;
  sprite.data = malloc(image.width * image.height * sizeof(unsigned int));

  color_t *current_color = (color_t *)image.data;
  for (int y = 0; y < image.height; y++) {
    for (int x = 0; x < image.width; x++) {
      int pos = x + y * image.width;
      sprite.data[pos] = map_rgba(current_color);
      current_color++;
    }
  }

  if (free_image) {
    unload_image(image);
  }

  return sprite;
}

void clear_sprite(sprite_t image) { free(image.data); }

void draw(sprite_t sprite) {
  bool out_of_bounds =
      sprite.position.x < -sprite.width || sprite.position.x > surface->w ||
      sprite.position.y < -sprite.height || sprite.position.y > surface->h;

  if (out_of_bounds)
    return;

  unsigned int *pixels = surface->pixels;

  for (int y = 0; y < sprite.height; y++) {
    for (int x = 0; x < sprite.width; x++) {
      int pixel_pos =
          (x + sprite.position.x) + (y + sprite.position.y) * surface->w;

      if (x < -sprite.position.x || y < -sprite.position.y || x > surface->w ||
          y > surface->h) {
        continue;
      }

      pixels[pixel_pos] = sprite.data[x + y * sprite.width];
    }
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
    SDL_FillRect(surface, NULL, 0);

    fps();
  }

  if (scene.unload != NULL) {
    scene.unload();
  }

  SDL_Quit();
}