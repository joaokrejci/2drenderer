#include "dynamic_entity.h"

void move_dynamic_entity(dynamic_entity_t * entity, double delta) {
    entity->position.x += (float) delta * entity->velocity.x;
    entity->position.y += (float) delta * entity->velocity.y;
}

void move_dynamic_entity_to_destination(dynamic_entity_t * entity, vec2_t destination, double delta) {
    int isPositionEqual = !point_compare(point_from_vec2(entity->position), point_from_vec2(destination));
    if(isPositionEqual) return;

    vec2_t direction = vec2_subtraction(destination, entity->position);
    vec2_t normalized_direction = vec2_normalized(direction);
    entity->velocity = vec2_scalar_product(normalized_direction, vec2_modulo(direction));
    move_dynamic_entity(entity, delta);
}
