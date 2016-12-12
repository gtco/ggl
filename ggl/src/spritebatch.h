#pragma once

#include "ggl.h"
#include "vertex.h"
#include <glm/glm.hpp>
#include <vector>

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

struct ggl_glyph
{
	GLuint texture;
	float depth;

	struct ggl_vertex top_left;
	struct ggl_vertex bottom_left;
	struct ggl_vertex top_right;
	struct ggl_vertex bottom_right;
};

class RenderBatch
{
public:
	RenderBatch(GLuint offset, GLuint num_vertices, GLuint texture) : offset_(offset), num_vertices_(num_vertices), texture_(texture)
	{
	}

	GLuint offset_;
	GLuint num_vertices_;
	GLuint texture_;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin(GlyphSortType sort_type = GlyphSortType::TEXTURE);
    // destination rectangle vec4 containing both position and size => x, y, z, w (z is width, w is height)
	void draw(const glm::vec4& destination_rectangle, const glm::vec4& uv_rectangle, float depth, GLuint texture, const ggl_color& color);
	void end();
	void render_batch();

private:
	void create_render_batches();
    void create_vertex_array();
	void sort_glyphs();

	static bool compareFrontToBack(ggl_glyph *a, ggl_glyph *b);
	static bool compareBackToFront(ggl_glyph *a, ggl_glyph *b);
	static bool compareTexture(ggl_glyph *a, ggl_glyph *b);

	GLuint vbo_id_;
	GLuint vao_id_;
	GlyphSortType sort_type_;
    std::vector<ggl_glyph*> glyphs_;
    std::vector<RenderBatch> render_batches_;
};