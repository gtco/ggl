#pragma once

#include "ggl.h"
#include "glsl.h"
#include "window.h"
#include "camera2d.h"
#include "spritebatch.h"
#include "inputmanager.h"

class Game
{
public:
	Game();
	~Game();
	bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
	void draw();
	void handle_events();
	void update(uint32_t elapsed);
	bool is_running() { return is_running_; };

private:
	bool is_running_;
	Window window_;
	Glsl glsl_;
	float interval_;
	Camera2d camera_;
	SpriteBatch sprite_batch_;
};