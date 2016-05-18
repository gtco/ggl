#pragma once

#include "ggl.h"

class Glsl
{
public:
	void init(const char* vertex_fp, const char* fragment_fp);
	void compile_shaders(const char* vertex_fp, const char* fragment_fp);
	void compile_shader(GLuint id, const char* fp);
	void link_shaders();
	void bind_attribute();
	GLint get_uniform_location(const char *uniformName);
	void enable_shaders();
	void disable_shaders();

private:
	GLuint program_id_;
	GLuint vertex_id_;
	GLuint fragment_id_;
};