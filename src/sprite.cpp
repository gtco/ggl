#include "sprite.h"
#include "vertex.h"

bool Sprite::init(float x, float y, float height, float width, const char* texture_filename)
{
    x_ = x;
    y_ = y;
    height_ = height;
    width_ = width;
	vbo_id_ = 0;
    
    if (vbo_id_ == 0)
    {
        glGenBuffers(1, &vbo_id_);
    }

    struct ggl_vertex vertex_data[6];

    ggl_vertex_set_position(&vertex_data[0], x_ + width_, y_ + height_);
    ggl_vertex_set_uv(&vertex_data[0], 1.0f, 1.0f);

    ggl_vertex_set_position(&vertex_data[1], x_, y_ + height_);
    ggl_vertex_set_uv(&vertex_data[1], 0.0f, 1.0f);

    ggl_vertex_set_position(&vertex_data[2], x_, y_);
    ggl_vertex_set_uv(&vertex_data[2], 0.0f, 0.0f);

    ggl_vertex_set_position(&vertex_data[3], x_, y_);
    ggl_vertex_set_uv(&vertex_data[3], 0.0f, 0.0f);

    ggl_vertex_set_position(&vertex_data[4], x_ + width_, y_);
    ggl_vertex_set_uv(&vertex_data[4], 1.0f, 0.0f);

    ggl_vertex_set_position(&vertex_data[5], x_ + width_, y_ + height_);
    ggl_vertex_set_uv(&vertex_data[5], 1.0f, 1.0f);


	for (int i = 0; i < 6; i++)
	{
        ggl_vertex_set_color(&vertex_data[i], 255, 255, 255, 255);
	}

	//Tell opengl to bind our vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
	//Upload the data to the GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	//Unbind the buffer (optional)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
	texture_ = new Texture();
    texture_->load(texture_filename);

    return true;
}

void Sprite::draw()
{
    //bind the texture object
    glBindTexture(GL_TEXTURE_2D, texture_->get_id());

	//bind the buffer object
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
    
    // 6 = # of vertices
    glDrawArrays(GL_TRIANGLES, 0, 6);
	//Disable the vertex attrib array. This is not optional.
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
	//Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

