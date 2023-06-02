#include <stdio.h>
#include <pthread.h>

#include "renderer.h"

#define VELOCITY 10

static sprite_t sprite;

static void load() { 
    sprite = create_sprite(load_image("sdl.png"), true);
    sprite.position.x = 10;
    sprite.position.y = 20;
}

static void loop() {
    draw(sprite);
}

static void unload() { clear_sprite(sprite); }

static void event_handler(SDL_Event event) {
  if (event.key.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_d) {
      sprite.position.x += VELOCITY;
    }
    if (event.key.keysym.sym == SDLK_a) {
      sprite.position.x -= VELOCITY;
    }
    if (event.key.keysym.sym == SDLK_w) {
      sprite.position.y -= VELOCITY;
    }
    if (event.key.keysym.sym == SDLK_s) {
      sprite.position.y += VELOCITY;
    }
  }

  if(event.type == SDL_MOUSEBUTTONDOWN) {
    sprite.position.x = event.button.x;
    sprite.position.y = event.button.y;
  }
}

static void * start_routine(void * args) {
  scene_t scene;
  scene.load = load;
  scene.loop = loop;
  scene.unload = unload;
  scene.event_handler = event_handler;

  init();
  start(scene);
}

int main() {
  pthread_t render_thread;
  pthread_create(&render_thread, NULL, start_routine, NULL);

  pthread_join(render_thread, NULL);
}