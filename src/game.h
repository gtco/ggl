#pragma once


#include "ggl.h"
#include "scene.h"

struct ggl_game {
	bool is_running_;
	SDL_Window *window_;
	SDL_Renderer *renderer_;
	struct ggl_scene *current_scene;
    SDL_GLContext gl_context_;
};

struct ggl_game *ggl_game_create();
void ggl_game_destroy(struct ggl_game *game);
bool ggl_game_init(struct ggl_game *game, const char* title, int xpos, int ypos, int height, int width, int flags);
void ggl_game_render(struct ggl_game *game);
void ggl_game_handle_events(struct ggl_game *game);
void ggl_game_update(struct ggl_game *game, uint32_t elapsed);


struct ggl_sprite {
    float x;
    float y;
    float width;
    float height;
    GLuint vbo_id;
};

struct ggl_sprite *ggl_sprite_create();
bool ggl_sprite_init(struct ggl_sprite *sprite, float x, float y, float height, float width);
void ggl_sprite_draw(struct ggl_sprite *sprite);
void ggl_sprite_destroy(struct ggl_sprite *sprite);
