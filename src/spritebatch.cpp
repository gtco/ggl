#include "spritebatch.h"

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

void SpriteBatch::begin()
{
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

void SpriteBatch::end()
{
}

void SpriteBatch::render_batch()
{
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