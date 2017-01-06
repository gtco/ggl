#pragma once

#include "ggl.h"
#include "vertex.h"

#ifdef __cplusplus
extern "C" {
#endif

    void ggl_spritebatch_begin();
    // destination rectangle vec4 containing both position and size => x, y, z, w (z is width, w is height)
    void ggl_spritebatch_draw(struct ggl_vec4 destination_rectangle, struct ggl_vec4 uv_rectangle, float depth, GLuint texture, struct ggl_color color);
    void ggl_spritebatch_end();
    void ggl_spritebatch_render_batch();


    void ggl_spritebatch_create_render_batches();
    void ggl_spritebatch_create_vertex_array();
    void ggl_spritebatch_sort_glyphs();

    bool ggl_spritebatch_compareFrontToBack(struct ggl_glyph *a, struct ggl_glyph *b);
    bool ggl_spritebatch_compareBackToFront(struct ggl_glyph *a, struct ggl_glyph *b);
    bool ggl_spritebatch_compareTexture(struct ggl_glyph *a, struct ggl_glyph *b);

#ifdef __cplusplus
}
#endif
