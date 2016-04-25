#pragma once

#include "SDL.h"

class Game
{
	public:
		Game();
		~Game();

		bool Init(const char* title, int xpos, int ypos, int height, int width, int flags);
		void Render();
		void Update();
		void HandleEvents();
		void CleanUp();
		bool IsRunning() { return is_running_; }

	private:
		bool is_running_;

		SDL_Window* window_;
		SDL_Renderer* renderer_;
};

