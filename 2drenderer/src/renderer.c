#include <stdio.h>
#include <time.h>

#include "renderer.h"
#include "color.h"

SDL_Surface *surface;
static SDL_Window *window;

static time_t instant;
static clock_t frame_instant;
static long fps_counter;
static double delta_time = 1;

static camera_t camera;

void init() {
    SDL_Init(SDL_INIT_VIDEO);

    int width = 1280;
    int height = 720;

    camera.position = vec2(250, 0);
    camera.width = width;
    camera.height = height;

    window = SDL_CreateWindow("2d renderer", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height, 0);
    surface = SDL_GetWindowSurface(window);
    SDL_Surface *cloned_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_BGRA32, 0);
    memcpy(surface->format, cloned_surface->format, sizeof(SDL_PixelFormat));
    SDL_FreeSurface(cloned_surface);
}

point_t world_to_canvas_position(vec2_t world_position) {
    vec2_t camera_coord = vec2(
            world_position.x - camera.position.x,
            world_position.y - camera.position.y
    );
    return point_from_vec2(camera_coord);
}

vec2_t canvas_to_world_position(point_t canvas_position) {
    return vec2(
            camera.position.x + (float) canvas_position.x,
            camera.position.y + (float) canvas_position.y
    );
}

static void draw_line(sprite_t *sprite, unsigned int *pixels, int horizontal_length, unsigned int source_position,
                      unsigned int dest_position) {
    memcpy(
            pixels + dest_position,
            (*sprite).data + source_position,
            horizontal_length * sizeof(unsigned int)
    );
}

static void
draw_line_with_alpha(sprite_t *sprite, unsigned int *pixels, int horizontal_length, unsigned int source_position,
                     unsigned int dest_position) {
    for (int x = 0; x < horizontal_length; x++) {
        unsigned int source = (*sprite).data[source_position + x];
        if (source) {
            pixels[dest_position + x] = source;
        }
    }
}

static void
draw_primitive(sprite_t sprite, vec2_t world_position, unsigned int frame_offset, size_2d_t frame_size, int alpha) {
    point_t position = world_to_canvas_position(world_position);
    rect2_t sprite_rect = rect(vec2_from_point(position), vec2((float) frame_size.width, (float) frame_size.height));
    rect2_t camera_rect = rect(vec2(0, 0), vec2((float) surface->w, (float) surface->h));
    rect2_t render_rect = rect2_intersection(sprite_rect, camera_rect);

    unsigned int *pixels = surface->pixels;

    point_t render_position = point_from_vec2(render_rect.position);
    int vertical_length = (int) render_rect.size.y;
    int horizontal_length = (int) render_rect.size.x;
    int vertical_offset = position.y > 0 ? 0 : -position.y;
    int horizontal_offset = position.x > 0 ? 0 : -position.x;


    for (int y = 0; y < vertical_length; y++) {
        unsigned int source_position =
                horizontal_offset
                + (y + vertical_offset) * sprite.width
                + frame_offset;
        unsigned int dest_position =
                render_position.x
                + (render_position.y + y) * (int) camera_rect.size.x;

        if (alpha) {
            draw_line_with_alpha(&sprite, pixels, horizontal_length, source_position, dest_position);
        } else {
            draw_line(&sprite, pixels, horizontal_length, source_position, dest_position);
        }
    }
}

void draw(sprite_t sprite, vec2_t position, int alpha) {
    size_2d_t sprite_size = {sprite.width, sprite.height};
    draw_primitive(sprite, position, 0, sprite_size, alpha);
}

void draw_animated(animated_sprite_t *animated_sprite, vec2_t position, int alpha) {
    double elapsed_time = (double) (clock() - animated_sprite->_last_frame_step) / CLOCKS_PER_SEC;
    double millis_per_second = 1.0 / animated_sprite->fps;

    if (elapsed_time >= millis_per_second) {
        advance_frame(animated_sprite);
        animated_sprite->_last_frame_step = clock();
    }

    unsigned int frame_offset = animated_sprite->current_frame * animated_sprite->frame_size.width;
    draw_primitive(animated_sprite->sprite, position, frame_offset, animated_sprite->frame_size, alpha);
}

static void fps() {
    if (instant < time(NULL)) {
        printf("\r fps: %ld ", fps_counter);
        fflush(stdout);

        instant = time(NULL);
        fps_counter = 0;
    } else {
        fps_counter++;
    }
}

static double delta() {
    clock_t new_instant = clock();
    delta_time = ((double) (new_instant - frame_instant)) / CLOCKS_PER_SEC;
    frame_instant = new_instant;
    return delta_time;
}

void start(scene_t scene) {
    instant = time(NULL);
    fps_counter = 0;
    frame_instant = clock();

    if (scene.load != NULL) {
        scene.load();
    }

    SDL_Event event;
    while (event.type != SDL_QUIT) {
        int poll_result = SDL_PollEvent(&event);

        if (scene.event_handler != NULL && poll_result) {
            scene.event_handler(event);
        }

        if (scene.loop != NULL) {
            scene.loop(delta());
        }

        SDL_UpdateWindowSurface(window);

        if (scene.flags & FLAG_CLEAR_BACKGROUND) {
            SDL_FillRect(surface, NULL, 0);
        }

        fps();
    }

    if (scene.unload != NULL) {
        scene.unload();
    }

    SDL_Quit();
}

camera_t *camera_viewport() {
    return &camera;
}
