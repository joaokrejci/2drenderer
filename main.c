#include "2drenderer/src/renderer.h"
#include "2drenderer/src/animated_sprite.h"
#include "math/src/geometry.h"
#include "game/src/dynamic_entity.h"
#include "game/src/dot.h"

#define PLAYER_SPEED 150 // pixels/second
#define DOTS_AMOUNT 20

static struct dot dots[DOTS_AMOUNT];
static int dots_index = 0;

static dynamic_entity_t player;
static sprite_t background;
static camera_t * camera;

void load() {
    camera = camera_viewport();
    camera->position = vec2(0, 0);

    player.position = (vec2_t) {200,0};
    player.velocity = (vec2_t) {0,0};

    image_t background_image = load_image("../assets/background_island.png");
    image_t player_image = load_image("../assets/stealthman.png");
    image_t dot_image = load_image("../assets/dot.png");

    background = create_sprite(background_image);
    sprite_t player_sprite = create_sprite(player_image);
    sprite_t dot_sprite = create_sprite(dot_image);

    resize_sprite(&player_sprite, 2 * player_sprite.width, 2 * player_sprite.height);
    resize_sprite(&dot_sprite, 2 * dot_sprite.width, 2 *  dot_sprite.height);

    player.sprite = create_animated_sprite(player_sprite, player_sprite.width / 2, player_sprite.height, 4);
    dot_entity_prototype.sprite = create_animated_sprite(dot_sprite, dot_sprite.width / 2, dot_sprite.height, 5);

    free_image(background_image);
    free_image(player_image);
    free_image(dot_image);
}

void unload() {
    clear_sprite(background);
    clear_sprite(dot_entity_prototype.sprite.sprite);
    clear_sprite(player.sprite.sprite);
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

    draw(background, vec2(0,0), 0);
    draw_animated(&player.sprite, player.position, 1);
    for (int i = 0; i < dots_index; i++) {
        draw_animated(&dots[i].entity.sprite, dots[i].entity.position, 1);
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
        point_t destination_on_camera = {
                (*event).button.x,
                (*event).button.y
        };
        vec2_t world_destination = canvas_to_world_position(destination_on_camera);
        dots[dots_index] = spawn_dot(player.position, point_from_vec2(world_destination));
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
    scene.flags = 0;

    start(scene);
}