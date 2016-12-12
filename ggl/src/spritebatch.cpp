#include "spritebatch.h"
#include <algorithm>

SpriteBatch::SpriteBatch() : vbo_id_(0), vao_id_(0)
{
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::init()
{
    create_vertex_array();
}

void SpriteBatch::begin(GlyphSortType sort_type)
{
    sort_type_ = sort_type;
	render_batches_.clear();

	for (int i = 0; i < glyphs_.size(); i++)
	{
		delete glyphs_[i];
	}

	glyphs_.clear();
}

void SpriteBatch::end()
{
    sort_glyphs();
	create_render_batches();
}

void SpriteBatch::draw(const glm::vec4& destination_rectangle, const glm::vec4& uv_rectangle, float depth, GLuint texture, const ggl_color& color)
{
    ggl_glyph *g = new ggl_glyph();
    g->texture = texture;
    g->depth = depth;

    g->top_left.color = color;
    ggl_vertex_set_position(&g->top_left, destination_rectangle.x, destination_rectangle.y + destination_rectangle.w);
    ggl_vertex_set_uv(&g->top_left, uv_rectangle.x, uv_rectangle.y + uv_rectangle.w);

    g->bottom_left.color = color;
    ggl_vertex_set_position(&g->bottom_left, destination_rectangle.x, destination_rectangle.y);
    ggl_vertex_set_uv(&g->bottom_left, uv_rectangle.x, uv_rectangle.y);

    g->bottom_right.color = color;
    ggl_vertex_set_position(&g->bottom_right, destination_rectangle.x + destination_rectangle.z, destination_rectangle.y);
    ggl_vertex_set_uv(&g->bottom_right, uv_rectangle.x + uv_rectangle.z, uv_rectangle.y);

    g->top_right.color = color;
    ggl_vertex_set_position(&g->top_right, destination_rectangle.x + destination_rectangle.z, destination_rectangle.y + destination_rectangle.w);
    ggl_vertex_set_uv(&g->top_right, uv_rectangle.x + uv_rectangle.z, uv_rectangle.y + uv_rectangle.w);

    glyphs_.push_back(g);

}

void SpriteBatch::render_batch()
{
	glBindVertexArray(vao_id_);

	for (int i = 0; i < render_batches_.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, render_batches_[i].texture_);
		glDrawArrays(GL_TRIANGLES, render_batches_[i].offset_, render_batches_[i].num_vertices_);
	}

	glBindVertexArray(0);
}

void SpriteBatch::create_render_batches()
{
    std::vector<ggl_vertex> vertices;
    vertices.resize(glyphs_.size()*6);
    if (glyphs_.empty())
    {
        return;
    }

    render_batches_.emplace_back(0, 6, glyphs_[0]->texture);
    // vertex for first glyph / first batch
    int offset = 0;
    int cv = 0;
    vertices[cv++] = glyphs_[0]->top_left;
    vertices[cv++] = glyphs_[0]->bottom_left;
    vertices[cv++] = glyphs_[0]->bottom_right;
    vertices[cv++] = glyphs_[0]->bottom_right;
	vertices[cv++] = glyphs_[0]->top_right;
    vertices[cv++] = glyphs_[0]->top_left;
    offset += 6;

    for (int cg = 1; cg < glyphs_.size(); cg++)
    {
        if (glyphs_[cg]->texture != glyphs_[cg-1]->texture)
        {
            render_batches_.emplace_back(offset, 6, glyphs_[cg]->texture);
        }
        else
        {
            render_batches_.back().num_vertices_ += 6;
        }

        vertices[cv++] = glyphs_[cg]->top_left;
        vertices[cv++] = glyphs_[cg]->bottom_left;
        vertices[cv++] = glyphs_[cg]->bottom_right;
        vertices[cv++] = glyphs_[cg]->bottom_right;
		vertices[cv++] = glyphs_[cg]->top_right;
        vertices[cv++] = glyphs_[cg]->top_left;
        offset += 6;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
	// Orphan buffer
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ggl_vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(ggl_vertex), vertices.data());
}

void SpriteBatch::create_vertex_array()
{
    if (vao_id_ == 0)
    {
        glGenVertexArrays(1, &vao_id_);
    }
    glBindVertexArray(vao_id_);
    if (vbo_id_ == 0)
    {
        glGenBuffers(1, &vbo_id_);
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);

    // Position
    glEnableVertexAttribArray(0);
    // Color
    glEnableVertexAttribArray(1);
    // UV
    glEnableVertexAttribArray(2);

    // Position Attribute Pointer : 2 = elements (x,y)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct ggl_vertex), (void *) offsetof(struct ggl_vertex, position));
    // Color Attribute Pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(struct ggl_vertex), (void *) offsetof(struct ggl_vertex, color));
    // UV Attribute Pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct ggl_vertex), (void *) offsetof(struct ggl_vertex, uv));

    glBindVertexArray(0);
}

void SpriteBatch::sort_glyphs()
{
	switch (sort_type_)
	{
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(glyphs_.begin(), glyphs_.end(), compareBackToFront);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(glyphs_.begin(), glyphs_.end(), compareFrontToBack);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(glyphs_.begin(), glyphs_.end(), compareTexture);
		break;
	}
}

bool SpriteBatch::compareFrontToBack(ggl_glyph *a, ggl_glyph *b)
{
    return (a->depth < b->depth);
}

bool SpriteBatch::compareBackToFront(ggl_glyph *a, ggl_glyph *b)
{
    return (a->depth > b->depth);
}

bool SpriteBatch::compareTexture(ggl_glyph *a, ggl_glyph *b)
{
    return (a->texture < b->texture);
}
