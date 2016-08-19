#pragma once

#include <unordered_map>

class InputManager
{
public:
	InputManager();
	~InputManager();
	void press_key(uint32_t key_id);
	void release_key(uint32_t key_id);
	bool is_key_pressed(uint32_t key_id);

private:
	std::unordered_map<uint32_t, bool> key_map_;

};
