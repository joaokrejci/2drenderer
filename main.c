#include "2drenderer/src/renderer.h"
#include "engine/src/game_object.h"

sprite_t car_sprite;
struct {
    game_object_t data[16];
    int length;
    int index;
} objects;

void load() {
    objects.length = 0;
    objects.index = 0;

    car_sprite = create_sprite(load_image("../assets/car.png"), 1);
    resize_sprite(&car_sprite, car_sprite.width * 2, car_sprite.height * 2);
}

void unload() {
    clear_sprite(car_sprite);
}

void loop() {
    for (int i = 0; i < objects.length; i++) {
        draw(objects.data[i].sprite, objects.data[i].position);
        i++;
    }
}

void event_handler(SDL_Event event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        game_object_t * new_obj = &objects.data[objects.index];
        new_obj->sprite = car_sprite;
        new_obj->position.x = event.button.x;
        new_obj->position.y = event.button.y;
        new_obj->height = new_obj->sprite.height;
        new_obj->width = new_obj->sprite.width;
        if(objects.length < 16) {
            objects.length++;
        }
        objects.index = (objects.index + 1) % 16;
    }
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