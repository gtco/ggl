#pragma once

#include "ggl.h"
#include "vertex.h"
#include <glm/glm.hpp>
#include <vector>

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
    // destination rectangle vec4 containing both position and size => x, y, z, w (z is width, w is height)  
	void draw(const glm::vec4& destination_rectangle, const glm::vec4& uv_rectangle, float depth, GLuint texture, const ggl_color& color);
	void end();
	
	void render_batch();

private:

    void create_vertex_array();
    
	GLuint vbo_id_;
	GLuint vao_id_;
    
    std::vector<ggl_glyph*> glyphs_;

};