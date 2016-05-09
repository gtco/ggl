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

    vertex_data[0].position.x = x + width;
    vertex_data[0].position.y = y + height;

    vertex_data[1].position.x = x;
    vertex_data[1].position.y = y + width;

    vertex_data[2].position.x = x;
    vertex_data[2].position.y = y;    

    vertex_data[3].position.x = x;
    vertex_data[3].position.y = y;

    vertex_data[4].position.x = x + width;
    vertex_data[4].position.y = y;

    vertex_data[5].position.x = x + width;
    vertex_data[5].position.y = y + width;    

	for (int i = 0; i < 6; i++)
	{
		vertex_data[i].color.r = 255;
		vertex_data[i].color.g = 133;
		vertex_data[i].color.b = 152;
		vertex_data[i].color.a = 255;
	}

    glBindBuffer(GL_ARRAY_BUFFER, sprite->vbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    return true;
}

void ggl_sprite_draw(struct ggl_sprite *sprite)
{
    glBindBuffer(GL_ARRAY_BUFFER, sprite->vbo_id);
    
    glEnableVertexAttribArray(0);
    
    // Position Attribute Pointer : 2 = elements (x,y)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct ggl_vertex), (void *) offsetof(struct ggl_vertex, position));

    // Color Attribute Pointer 
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(struct ggl_vertex), (void *) offsetof(struct ggl_vertex, color));    
    
    // 6 = # of vertices
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(0);
    
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
