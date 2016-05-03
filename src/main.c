#include "ggl.h"
#include "game.h"

/*
void load_image()
{
	SDL_Surface *surface = IMG_Load("data/8tiles.png");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	//	SDL_QueryTexture(texture, NULL, NULL, &sourceRect.w, &sourceRect.h);

	int i = 6;
	int n = (32 * i) + ((i + 1) * 10);

	sourceRect.w = 32;
	sourceRect.h = 32;

	sourceRect.x = n;
	sourceRect.y = 10;
	destRect.x = (SCREEN_WIDTH/2) - 16;
	destRect.y = (SCREEN_HEIGHT/2) - 16;

	destRect.w = sourceRect.w;
	destRect.h = sourceRect.h;
}
*/

int main(int argc, char** argv)
{
	debug("Starting game");
	struct ggl_game *game = ggl_game_create();

	ggl_game_init(game, "GGL", 100, 100, 640, 480, 0);

	uint32_t last = SDL_GetTicks();
	while (game->is_running_)
	{
		uint32_t current = SDL_GetTicks();
		uint32_t elapsed = current - last;
		ggl_game_handle_events(game);
		ggl_game_update(game, elapsed);
		ggl_game_render(game);
	}

	debug("Ending game");
	ggl_game_destroy(game);
	exit(0);
}
