#include "SDL.h"
#include "SDL_image.h"

SDL_Window	*window = 0;
SDL_Renderer *renderer = 0;
SDL_Texture *texture = 0;
SDL_Rect sourceRect;
SDL_Rect destRect;

const int MS_PER_FRAME = 33;
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;

bool running = false;

bool init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos,
			height, width,
			flags);

		if (window != 0)
		{
			// window, drive, render flags
			renderer = SDL_CreateRenderer(window, -1, 0);
		}
	}
	else
	{
		return false;
	}

	return true;
}

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

void render()
{
	// renderer, red, green, blue, alpha
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, texture, &sourceRect, &destRect);

	SDL_RenderPresent(renderer);

}

void handle_events()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		default:
			break;
		}
	}
}

int main(int argc, char** argv)
{
	running = init("SDL2",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (!running)
	{
		return 1;
	}

	load_image();

	unsigned long then = 0;
	unsigned long now = 0;
	double lastTime = 0;

	while (running)
	{
		then = now;
		now = SDL_GetTicks();

		handle_events();
		// process_input
		// update(elapsed)
		render();

		long elapsed = (long)(now - then);
		int delay = MS_PER_FRAME - elapsed;
		SDL_Delay(delay > 0 ? delay : 0);
	}

	SDL_Quit();

	exit(0);
}
