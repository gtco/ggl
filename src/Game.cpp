#include "Game.h"

bool Game::Init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		window_ = SDL_CreateWindow(title, xpos, ypos,
			height, width,
			flags);

		if (window_ != 0)
		{
			// window, drive, render flags
			renderer_ = SDL_CreateRenderer(window_, -1, 0);
		}
	}
	else
	{
		return false;
	}

	return true;
}

void Game::Render()
{
	// renderer, red, green, blue, alpha
	SDL_SetRenderDrawColor(renderer_, 0xD0, 0xD0, 0xD0, 0xff);
	SDL_RenderClear(renderer_);
//	SDL_RenderCopy(renderer_, texture, &sourceRect, &destRect);
	SDL_RenderPresent(renderer_);
}

void Game::CleanUp()
{
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
	SDL_Quit();
}

void Game::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			is_running_ = false;
			break;
		default:
			break;
		}
	}
}