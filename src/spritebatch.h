#pragma once

#include "ggl.h"
#include "vertex.h"
#include <glm/glm.hpp>

struct ggl_glyph
{
	GLuint texture;
	float depth;

	struct ggl_vertex top_left;
	struct ggl_vertex bottom_left;
	struct ggl_vertex top_right;
	struct ggl_vertex bottom_right;	
};

class SpriteBatch 
{
public:
	SpriteBatch(); 
	~SpriteBatch();

	void init();

	void begin();
	void draw(const glm::vec4& destination_rectangle, const glm::vec4& uv_rectangle, GLuint texture, const ggl_color& color);
	void end();
	
	void render_batch();

private:

	GLuint vbo_id_;
	GLuint vao_id_;

};