#pragma once

#include "ggl.h"
#include "texture.h"

class Sprite
{
public:
	bool init(float x, float y, float height, float width, const char* texture_filename);
	void draw();

private:
	float x_;
	float y_;
	float width_;
	float height_;
	GLuint vbo_id_;
	Texture *texture_;
};