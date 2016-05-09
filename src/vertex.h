#pragma once

#include "ggl.h"

// multiple of 4 bytes
struct ggl_vertex 
{
	struct ggl_vertex_position
	{
		float x;
		float y;
	} position;

	struct ggl_vertex_color
	{
		GLubyte r;
		GLubyte g;		
		GLubyte b;		
		GLubyte a;		
	} color;
};

