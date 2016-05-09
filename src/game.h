#pragma once


#include "ggl.h"
#include "scene.h"

struct ggl_game {
	bool is_running_;
	SDL_Window *window_;
	SDL_Renderer *renderer_;
    SDL_GLContext gl_context_;
    struct ggl_sprite *sprite_;
    struct ggl_glsl *glsl_;
};

struct ggl_game *ggl_game_create();
void ggl_game_destroy(struct ggl_game *game);
bool ggl_game_init(struct ggl_game *game, const char* title, int xpos, int ypos, int height, int width, int flags);
void ggl_game_render(struct ggl_game *game);
void ggl_game_handle_events(struct ggl_game *game);
void ggl_game_update(struct ggl_game *game, uint32_t elapsed);

