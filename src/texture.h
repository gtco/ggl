#pragma once

#include "ggl.h"

class Texture
{
public:
	void load(const char* filename);
	GLuint get_id() { return id_; };

private:
	GLuint id_;
	int width_;
	int height_;
};