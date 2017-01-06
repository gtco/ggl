#include "inputmanager.h"

InputManager::InputManager()
{
	mouse_coords_.x = 0;
	mouse_coords_.y = 0;

	for (int i = 0; i < 255; i++)
	{
		key_map_[i] = false;
	}
}

InputManager::~InputManager()
{
}

void InputManager::press_key(uint32_t key_id)
{
	key_map_[key_id] = true;
}

void InputManager::release_key(uint32_t key_id)
{
	key_map_[key_id] = false;
}

bool InputManager::is_key_pressed(uint32_t key_id)
{
	return key_map_[key_id];
}

void InputManager::set_mouse_coords(float x, float y)
{
	mouse_coords_.x = x;
	mouse_coords_.y = y;
}

ggl_vec2 InputManager::get_mouse_coords()
{
	return mouse_coords_;
}
