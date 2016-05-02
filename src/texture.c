#include "texture.h"

struct ggl_texture *ggl_texture_create()
{
	struct ggl_texture *texture = malloc(sizeof(struct ggl_texture));
	assert(texture != NULL);
	//TODO

	return texture;
}

void ggl_texture_load(struct ggl_texture *texture, SDL_Renderer* renderer, const char* filename)
{
	SDL_Surface *surface = IMG_Load(filename);
	texture->texture_ = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture->texture_, NULL, NULL, &texture->rect_.w, &texture->rect_.h);
}

void ggl_texture_destroy(struct ggl_texture *texture)
{
	assert(texture != NULL);
	SDL_DestroyTexture(texture->texture_);
	free(texture);
}

void ggl_texture_draw(struct ggl_texture *texture, int x, int y, int width, int height, SDL_Renderer* renderer)
{
	SDL_Rect destRect;

	int i = 6;
	int n = (32 * i) + ((i + 1) * 10);
	texture->rect_.x = n;
	texture->rect_.y = 10;
	
	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_RenderCopy(renderer, texture->texture_, &texture->rect_, &destRect);
}