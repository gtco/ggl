#pragma once

#include <stdio.h>
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
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#elif __linux__
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#endif

typedef struct {
  float x;
  float y;
} vec2;
