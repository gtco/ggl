#include "inputmanager.h"

InputManager::InputManager()
{
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
	auto it = key_map_.find(key_id);

	if (it != key_map_.end())
	{
		return key_map_[key_id];
	}
	else
	{
		return false;
	}
}