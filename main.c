#include "2drenderer/src/renderer.h"
#include "math/src/geometry.h"
#include "game/src/dynamic_entity.h"
#include "game/src/dot.h"

#define PLAYER_SPEED 150 // pixels/second
#define DOTS_AMOUNT 20

struct dot dots[DOTS_AMOUNT];

int dots_index = 0;

dynamic_entity_t player;

void load() {
    player.position = (vec2_t) {100,100};
    player.velocity = (vec2_t) {0,0};
    player.sprite = create_sprite(load_image("../assets/player.png"), 1);
    resize_sprite(&player.sprite, player.sprite.width * 2, player.sprite.height * 2);

    dot_entity_prototype.sprite = create_sprite(load_image("../assets/dot.png"), 1);
}

void unload() {
    clear_sprite(player.sprite);
    clear_sprite(dot_entity_prototype.sprite);
}

void move_dots(double delta) {
    struct dot *current_dot;
    for (int i = 0; i < dots_index; i++) {
        current_dot = &dots[i];
        move_dynamic_entity_to_destination(&current_dot->entity, current_dot->destination, delta);
    }
}

void loop(double delta) {
    move_dynamic_entity(&player, delta);
    move_dots(delta);

    draw(player.sprite, point_from_vec2(player.position));
    for (int i = 0; i < dots_index; i++) {
        draw(dots[i].entity.sprite, point_from_vec2(dots[i].entity.position));
    }
}

void player_input_handler(SDL_Event *event) {
    if ((*event).key.type == SDL_KEYDOWN) {
        switch ((*event).key.keysym.sym) {
            case SDLK_w:
                player.velocity.y = -PLAYER_SPEED;
                break;
            case SDLK_s:
                player.velocity.y = PLAYER_SPEED;
                break;
            case SDLK_a:
                player.velocity.x = -PLAYER_SPEED;
                break;
            case SDLK_d:
                player.velocity.x = PLAYER_SPEED;
                break;
        }
    }
    if ((*event).key.type == SDL_KEYUP) {
        switch ((*event).key.keysym.sym) {
            case SDLK_w:
            case SDLK_s:
                player.velocity.y = 0;
                break;
            case SDLK_a:
            case SDLK_d:
                player.velocity.x = 0;
                break;
        }
    }
}

void dots_input_handler(SDL_Event *event) {
    if ((*event).button.type == SDL_MOUSEBUTTONDOWN && (*event).button.button == SDL_BUTTON_LEFT) {
        point_t destination = {
                (*event).button.x,
                (*event).button.y
        };
        dots[dots_index] = spawn_dot(player.position, destination);
        dots_index = (dots_index + 1)%DOTS_AMOUNT;
    }
}

void event_handler(SDL_Event event) {
    player_input_handler(&event);
    dots_input_handler(&event);
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