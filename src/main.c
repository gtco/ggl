#include "ggl.h"
#include "game.h"

int main(int argc, char** argv)
{
	debug("Starting game");
	struct ggl_game *game = ggl_game_create();

	ggl_game_init(game, "GGL", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

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
