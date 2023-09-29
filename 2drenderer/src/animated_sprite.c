#include "animated_sprite.h"

animated_sprite_t create_animated_sprite(sprite_t sprite, int frame_width, int frame_height, unsigned int fps) {
    animated_sprite_t animated_sprite;
    animated_sprite.sprite = sprite;
    animated_sprite.current_frame = 0;
    animated_sprite.fps = fps;
    animated_sprite.frame_size = (size_2d_t) {frame_width, frame_height};
    animated_sprite.frames = sprite.width / frame_width;
    animated_sprite._last_frame_step = clock();

    return animated_sprite;
}

void advance_frame(animated_sprite_t * animated_sprite) {
    animated_sprite->current_frame = (animated_sprite->current_frame + 1) % animated_sprite->frames;
}