#include "geometry.h"

int is_inside(vec2_t point, rectangle_t box) {
  return point.x >= box.x && point.x <= box.x + box.w && point.y >= box.y &&
         point.y <= box.y + box.h;
}