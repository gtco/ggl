#pragma once

#include "ggl.h"
#include "sprite.h"
#include "glsl.h"
#include "window.h"
#include "camera2d.h"

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
	Sprite player_;
	Sprite enemy_;
	Glsl glsl_;
	float interval_;
	Camera2d camera_;
};