#pragma once

#include "ggl.h"

struct ggl_glsl {
    GLuint program_id;
    GLuint vertex_id;
    GLuint fragment_id;
};

void ggl_glsl_compile_shaders(struct ggl_glsl *glsl, const char* vertex_fp, const char* fragment_fp);
void ggl_glsl_link_shaders(struct ggl_glsl *glsl);
char *ggl_glsl_read_file(const char* file_path);
void ggl_glsl_bind_attribute(struct ggl_glsl *glsl);