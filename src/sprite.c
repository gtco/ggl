#include "sprite.h"
#include "vertex.h"

struct ggl_sprite *ggl_sprite_create()
{
    struct ggl_sprite *sprite = malloc(sizeof(struct ggl_sprite));
    assert(sprite != NULL);

    sprite->x = 0;
    sprite->y = 0;
    sprite->height = 0;
    sprite->width = 0;
    sprite->vbo_id = 0;
    
    return sprite;
    
}

bool ggl_sprite_init(struct ggl_sprite *sprite, float x, float y, float height, float width)
{
    sprite->x = x;
    sprite->y = y;
    sprite->height = height;
    sprite->width = width;
    
    if (sprite->vbo_id == 0)
    {
        glGenBuffers(1, &sprite->vbo_id);
    }

    struct ggl_vertex vertex_data[6];

    ggl_vertex_set_position(&vertex_data[0], x + width, y + height);
    ggl_vertex_set_uv(&vertex_data[0], 1.0f, 1.0f);

    ggl_vertex_set_position(&vertex_data[1], x, y + height);
    ggl_vertex_set_uv(&vertex_data[1], 0.0f, 1.0f);

    ggl_vertex_set_position(&vertex_data[2], x, y);
    ggl_vertex_set_uv(&vertex_data[2], 0.0f, 0.0f);

    ggl_vertex_set_position(&vertex_data[3], x, y);
    ggl_vertex_set_uv(&vertex_data[3], 0.0f, 0.0f);

    ggl_vertex_set_position(&vertex_data[4], x + width, y);
    ggl_vertex_set_uv(&vertex_data[4], 1.0f, 0.0f);

    ggl_vertex_set_position(&vertex_data[5], x + width, y + height);
    ggl_vertex_set_uv(&vertex_data[5], 1.0f, 1.0f);


	for (int i = 0; i < 6; i++)
	{
        ggl_vertex_set_color(&vertex_data[i], 255, 255, 255, 255);
	}

	//Tell opengl to bind our vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, sprite->vbo_id);
	//Upload the data to the GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	//Unbind the buffer (optional)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    return true;
}

void ggl_sprite_draw(struct ggl_sprite *sprite)
{
	//bind the buffer object
    glBindBuffer(GL_ARRAY_BUFFER, sprite->vbo_id);
    
	//Tell opengl that we want to use the first
	//attribute array. We only need one array right
	//now since we are only using position.
    glEnableVertexAttribArray(0);
    
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
	//Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ggl_sprite_destroy(struct ggl_sprite *sprite)
{
    assert(sprite != NULL);

    if (sprite->vbo_id != 0)
    {
        glDeleteBuffers(1, &sprite->vbo_id);
    }

    free(sprite);
}
