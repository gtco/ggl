#pragma once

#include "ggl.h"

#ifdef __cplusplus
extern "C" {
#endif

void ggl_inputmanager_press_key(uint32_t key_id);
void ggl_inputmanager_release_key(uint32_t key_id);
bool ggl_inputmanager_is_key_pressed(uint32_t key_id);

#ifdef __cplusplus
}
#endif

