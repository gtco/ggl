#pragma once

#include "ggl.h"

struct ggl_vec2
{
	float x;
	float y;
};

struct ggl_color
{
	GLubyte r;
	GLubyte g;		
	GLubyte b;		
	GLubyte a;		
};

// must be multiple of 4 bytes
struct ggl_vertex 
{
	struct ggl_vec2 position;
	struct ggl_color color;
};

