#pragma once

#include "ggl.h"

#ifdef __cplusplus
extern "C" {
#endif

	void ggl_calculate_fps(uint32_t elapsed);
	void ggl_limit_fps(uint32_t start);

#ifdef __cplusplus
}
#endif




