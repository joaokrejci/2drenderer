#include "dot.h"
#include <string.h>

dynamic_entity_t dot_entity_prototype;

dot_t spawn_dot(vec2_t origin, point_t destination) {
    dot_t new_dot;
    memcpy(&(new_dot.entity), &dot_entity_prototype, sizeof (dynamic_entity_t));
    new_dot.entity.position = origin;
    new_dot.destination = vec2_from_point(destination);
    return new_dot;
}