#pragma once

#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "dbg.h"

#ifdef _WIN32
#include "SDL.h"
#include "SDL_image.h"
#include "GL/glew.h"
#elif __APPLE__
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#elif __linux__
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#endif

typedef struct {
  float x;
  float y;
} vec2;
