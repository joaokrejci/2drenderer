#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

image_t load_image(const char *path) {
  image_t sprite;
  sprite.data = stbi_load(path, &sprite.width, &sprite.height, &sprite.channels,
                          SPRITE_COLOR_CHANELS);
  return sprite;
}

void free_image(image_t image) { stbi_image_free(image.data); }