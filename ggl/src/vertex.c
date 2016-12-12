#include "vertex.h"

void ggl_vertex_set_color(struct ggl_vertex *vertex, GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	vertex->color.r = r;
	vertex->color.g = g;
	vertex->color.b = b;
	vertex->color.a = a;
}

void ggl_vertex_set_uv(struct ggl_vertex *vertex, float u, float v)
{
	vertex->uv.u = u;
	vertex->uv.v = v;
}

void ggl_vertex_set_position(struct ggl_vertex *vertex, float x, float y)
{
	vertex->position.x = x;
	vertex->position.y = y;
}
