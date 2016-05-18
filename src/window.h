#pragma once

#include "ggl.h"

class Window
{
public:
	Window();
	~Window();

	bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
	void swap();

private:
	SDL_Window *window_;
	SDL_Renderer *renderer_;
	SDL_GLContext gl_context_;
};