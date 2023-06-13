#include "2drenderer/src/renderer.h"
#include "engine/src/game_object.h"
#include "engine/src/dynamic_array.h"

sprite_t car_sprite;
dynamic_array_t game_objects;

void load() {
    game_objects = create_dynamic_array(sizeof (game_object_t));

    car_sprite = create_sprite(load_image("../assets/car.png"), 1);
    resize_sprite(&car_sprite, car_sprite.width * 2, car_sprite.height * 2);
}

void unload() {
    clear_sprite(car_sprite);
    delete_dynamic_array(&game_objects);
}

void loop() {
    game_object_t * object = (game_object_t *) game_objects.data;
    for (int i = 0; i < game_objects.length; i++) {
        draw(object->sprite, object->position);
        object++;
    }
}

void event_handler(SDL_Event event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        game_object_t new_obj;
        new_obj.sprite = car_sprite;
        new_obj.position.x = event.button.x;
        new_obj.position.y = event.button.y;
        new_obj.height = new_obj.sprite.height;
        new_obj.width = new_obj.sprite.width;
        dynamic_array_insert(&game_objects, (unsigned char *) &new_obj, 1);
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