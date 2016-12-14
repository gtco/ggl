#include "inputmanager.h"

bool key_map[255];

void ggl_inputmanager_press_key(uint32_t key_id)
{
	key_map[key_id] = true;
}

void ggl_inputmanager_release_key(uint32_t key_id)
{
	key_map[key_id] = false;
}

bool ggl_inputmanager_is_key_pressed(uint32_t key_id)
{
	return key_map[key_id];
}
