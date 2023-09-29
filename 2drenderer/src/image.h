#ifndef IMAGE_H
#define IMAGE_H

#define SPRITE_COLOR_CHANELS 4
typedef struct image {
  int width, height, channels;
  unsigned char *data;
} image_t;

image_t load_image(const char *path);
void free_image(image_t image);

#endif