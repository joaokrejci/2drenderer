#include <SDL2/SDL.h>

#include "sprite.h"
#include "color.h"

extern SDL_Surface * surface;

static unsigned int map_rgba(color_t *color) {
  return SDL_MapRGBA(surface->format, color->r, color->g, color->b, color->a);
}

sprite_t create_sprite(image_t image, int free_image) {
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
