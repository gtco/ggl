#include "ggl.h"
#include "game.h"
#include "tree.h"

float fps = 0.0f;
uint32_t frame_times[100];
uint32_t current_frame = 0;

void ggl_calculate_fps(uint32_t elapsed);

int main(int argc, char** argv)
{
	debug("Starting game");
	struct ggl_game *game = ggl_game_create();

	ggl_game_init(game, "GGL", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	uint32_t last = SDL_GetTicks();
	uint32_t current = SDL_GetTicks();
	uint32_t elapsed = current - last;

	while (game->is_running_)
	{
		ggl_game_handle_events(game);
		ggl_game_update(game, elapsed);
		ggl_game_render(game);

		current = SDL_GetTicks();
		elapsed = current - last;
		last = current;
		ggl_calculate_fps(elapsed);
	}

	debug("Ending game");
	ggl_game_destroy(game);
	exit(0);
}


void ggl_calculate_fps(uint32_t elapsed)
{
	if (!(current_frame % 10 == 0))
	{
		current_frame++;
		return;
	}

	int frame_count;
	frame_times[current_frame % 100] = elapsed;
	if (current_frame < 100)
	{
		fps = 0;
	}
	else
	{
		frame_count = 100;
		uint32_t total_sum = 0.0f;
		for (int i = 0; i < 100; i++)
		{
			total_sum += frame_times[i];
		}

		total_sum /= frame_count;

		fps = (total_sum > 0) ? 1000.0f / total_sum : 1001.0f;
	}

	current_frame++;

	debug("fps = %f", fps);
}
