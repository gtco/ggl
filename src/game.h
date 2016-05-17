#pragma once

#include "ggl.h"
#include "sprite.h"
#include "glsl.h"

class Game
{
public:
	Game();
	~Game();
	bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
	void render();
	void handle_events();
	void update(uint32_t elapsed);
	bool is_running() { return is_running_; };

private:
	bool is_running_;
	SDL_Window *window_;
	SDL_Renderer *renderer_;
	SDL_GLContext gl_context_;
	Sprite *sprite_;
	Glsl *glsl_;
	float interval_;
};