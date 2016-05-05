#include "game.h"

struct ggl_game *ggl_game_create() 
{
	struct ggl_game *game = malloc(sizeof(struct ggl_game));
	assert(game != NULL);
	game->is_running_ = false;
	//TODO

	return game;
}

bool ggl_game_init(struct ggl_game *game, const char* title, int xpos, int ypos, int height, int width, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		game->window_ = SDL_CreateWindow(title, xpos, ypos, height, width,flags);

		if (game->window_ != 0)
		{
			// window, drive, render flags
			game->renderer_ = SDL_CreateRenderer(game->window_, -1, 0);
		}
	}
	else
	{
		return false;
	}

	game->current_scene = ggl_scene_create();
	game->is_running_ = true;
	return true;
}

void ggl_game_destroy(struct ggl_game *game)
{
	assert(game != NULL);
	game->is_running_ = false;
	ggl_scene_destroy(game->current_scene);
	SDL_DestroyWindow(game->window_);
	SDL_DestroyRenderer(game->renderer_);
	free(game);
}

void ggl_game_render(struct ggl_game *game)
{
	// renderer, red, green, blue, alpha
	SDL_SetRenderDrawColor(game->renderer_, 0xff, 0x66, 0x00, 0xff);
	SDL_RenderClear(game->renderer_);
	ggl_scene_draw(game->current_scene, game->renderer_);
	SDL_RenderPresent(game->renderer_);
}

void ggl_game_handle_events(struct ggl_game *game)
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			game->is_running_ = false;
			break;
		default:
			break;
		}

		ggl_scene_handle_events(game->current_scene, event);
	}
}

void ggl_game_update(struct ggl_game * game, uint32_t elapsed)
{
	ggl_scene_update(game->current_scene, elapsed);
}
