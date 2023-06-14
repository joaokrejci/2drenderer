#include "2drenderer/src/renderer.h"

sprite_t cat_sprite;
animated_sprite_t animated_cat;

void load() {
    cat_sprite = create_sprite(load_image("../assets/cat-walk.png"), 1);
    resize_sprite(&cat_sprite, cat_sprite.width * 2, cat_sprite.height * 2);
    animated_cat = create_animated_sprite(cat_sprite, 16 * 2, 16 * 2, 8);
}

void unload() {
    clear_sprite(cat_sprite);
}

void loop() {
    position_t sprite_position = {100, 100};
    draw_animated(animated_cat, sprite_position);
}

void event_handler(SDL_Event event) {
    advance_frame(&animated_cat);
}

int main() {
    init();

    scene_t scene;
    scene.load = load;
    scene.unload = unload;
    scene.loop = loop;
    scene.event_handler = event_handler;
    scene.flags = FLAG_CLEAR_BACKGROUND;

    start(scene);
}