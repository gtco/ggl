#include "ggl.h"
#include "game.h"
#include "tree.h"

float fps = 0.0f;
uint32_t frame_times[99];
uint32_t current_frame = 0;

void ggl_calculate_fps(uint32_t elapsed);

int main(int argc, char** argv)
{
	debug("Starting game");
	Game *game = new Game();

	game->init("GGL", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	uint32_t last = SDL_GetTicks();
	uint32_t current = 0;
	uint32_t elapsed = 0;;

	while (game->is_running())
	{
		current = SDL_GetTicks();
		elapsed = current - last;

		game->handle_events();
		game->update(elapsed);
		game->draw();

		last = current;

		ggl_calculate_fps(elapsed);
	}

	debug("Ending game");
	exit(0);
}

void ggl_calculate_fps(uint32_t elapsed)
{
	if (current_frame++ < 100)
	{
		frame_times[current_frame % 99] = elapsed;
		return;
	}
	
	frame_times[current_frame % 99] = elapsed;

	if (current_frame % 10000 == 0) {

		uint32_t total_sum = 0.0f;
		for (int i = 0; i < 99; i++)
		{
			total_sum += frame_times[i];
		}

		total_sum /= 100;

		fps = (total_sum > 0) ? 1000.0f / total_sum : 1001.0f;
//		debug("fps = %f", fps);
	}
}
