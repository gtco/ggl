#pragma once

#include "ggl.h"

struct ggl_sprite {
    float x;
    float y;
    float width;
    float height;
    GLuint vbo_id;
};

struct ggl_sprite *ggl_sprite_create();
bool ggl_sprite_init(struct ggl_sprite *sprite, float x, float y, float height, float width);
void ggl_sprite_draw(struct ggl_sprite *sprite);
void ggl_sprite_destroy(struct ggl_sprite *sprite);
