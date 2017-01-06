#include "simplebatch.h"

/*
GLuint vbo_id_;
GLuint vao_id_;
GlyphSortType sort_type_;
std::vector<ggl_glyph*> glyphs_;
std::vector<RenderBatch> render_batches_;
*/

struct ggl_renderbatch render_batches[32];
struct ggl_glyph *glyphs[256];

static struct ggl_renderbatch empty_batch = { 0, 0, 0 };


void ggl_spritebatch_begin()
{
/*
	render_batches_.clear();

	for (int i = 0; i < glyphs_.size(); i++)
	{
		delete glyphs_[i];
	}

	glyphs_.clear();
*/
}

void ggl_spritebatch_end()
{
    sort_glyphs();
	create_render_batches();
}

void ggl_spritebatch_draw(struct ggl_vec4 destination_rectangle, struct ggl_vec4 uv_rectangle, float depth, GLuint texture, struct ggl_color color)
{
    struct ggl_glyph *g = ggl_glyph_create();
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

void ggl_spritebatch_render_batch()
{
	glBindVertexArray(vao_id_);

	for (int i = 0; i < render_batches_.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, render_batches_[i].texture_);
		glDrawArrays(GL_TRIANGLES, render_batches_[i].offset_, render_batches_[i].num_vertices_);
	}

	glBindVertexArray(0);
}

void ggl_spritebatch_create_render_batches()
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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(struct ggl_vertex), 0, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(struct ggl_vertex), vertices.data());
}

void ggl_spritebatch_create_vertex_array()
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

void ggl_spritebatch_sort_glyphs()
{
	/*
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
	*/
}

bool ggl_spritebatch_compareFrontToBack(struct ggl_glyph *a, struct ggl_glyph *b)
{
    return (a->depth < b->depth);
}

bool ggl_spritebatch_compareBackToFront(struct ggl_glyph *a, struct ggl_glyph *b)
{
    return (a->depth > b->depth);
}

bool ggl_spritebatch_compareTexture(struct ggl_glyph *a, struct ggl_glyph *b)
{
    return (a->texture < b->texture);
}
