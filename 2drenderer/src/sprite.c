#include <SDL2/SDL.h>

#include "sprite.h"
#include "color.h"

extern SDL_Surface * surface;

static unsigned int map_rgba(color_t *color) {
    return SDL_MapRGBA(surface->format, color->r, color->g, color->b, color->a);
}

sprite_t create_sprite(image_t image) {
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

  return sprite;
}

void clear_sprite(sprite_t image) { free(image.data); }

void resize_sprite(sprite_t * sprite, int width, int height)
{
  unsigned int * new_data = malloc(sizeof(unsigned int) * width * height);

  int x_ratio = (int) ((sprite->width<<16) / width)+1;
  int y_ratio = (int) ((sprite->height<<16) / height)+1;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int px = (x * x_ratio)>>16;
      int py = (y * y_ratio)>>16;

      new_data[x + y * width] = sprite->data[px + py * sprite->width];
    }
  }

  clear_sprite(*sprite);
  sprite->data = new_data;
  sprite->height = height;
  sprite->width = width;
}
