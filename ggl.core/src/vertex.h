#pragma once

#include "ggl.h"

struct ggl_vec2
{
	float x;
	float y;
};

struct ggl_uv
{
	float u;
	float v;
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
	// UV texture coordinates
	struct ggl_uv uv;
};

#ifdef __cplusplus
extern "C" {
#endif

	void ggl_vertex_set_color(struct ggl_vertex *vertex, GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	void ggl_vertex_set_uv(struct ggl_vertex *vertex, float u, float v);
	void ggl_vertex_set_position(struct ggl_vertex *vertex, float x, float y);

#ifdef __cplusplus
}
#endif
