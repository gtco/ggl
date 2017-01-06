#pragma once

#include "ggl.h"
#include "vertex.h"

class InputManager
{
public:
	InputManager();
	~InputManager();
	void press_key(uint32_t key_id);
	void release_key(uint32_t key_id);
	bool is_key_pressed(uint32_t key_id);
	void set_mouse_coords(float x, float y);
	struct ggl_vec2 get_mouse_coords();

private:
	bool key_map_[255];
	struct ggl_vec2 mouse_coords_;
};
