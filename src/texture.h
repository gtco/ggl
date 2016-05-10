#pragma once

#include "ggl.h"

struct ggl_texture
{
	GLuint id_;
	int width_;
	int height_;
};

struct ggl_texture *ggl_texture_create();
void ggl_texture_load(struct ggl_texture *texture, const char* filename);
void ggl_texture_destroy(struct ggl_texture *texture);
