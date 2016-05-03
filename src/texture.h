#pragma once

#include <assert.h>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

struct ggl_texture
{
	SDL_Texture *texture_;
	SDL_Rect rect_;
};

struct ggl_texture *ggl_texture_create();
void ggl_texture_load(struct ggl_texture *texture, SDL_Renderer* renderer, const char* filename);
void ggl_texture_destroy(struct ggl_texture *texture);
void ggl_texture_draw(struct ggl_texture *texture, int x, int y, int width, int height, SDL_Renderer* renderer);
