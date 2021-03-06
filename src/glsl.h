#pragma once

#include "ggl.h"

struct ggl_glsl {
    GLuint program_id;
    GLuint vertex_id;
    GLuint fragment_id;
};


void ggl_glsl_init(struct ggl_glsl *glsl, const char* vertex_fp, const char* fragment_fp);

void ggl_glsl_compile_shaders(struct ggl_glsl *glsl, const char* vertex_fp, const char* fragment_fp);
void ggl_glsl_compile_shader(GLuint id, const char* fp);
void ggl_glsl_link_shaders(struct ggl_glsl *glsl);
void ggl_glsl_bind_attribute(struct ggl_glsl *glsl);
void ggl_glsl_destroy(struct ggl_glsl *glsl);
GLint ggl_glsl_get_uniform_location(struct ggl_glsl *glsl, const char *uniformName);

struct ggl_glsl *ggl_glsl_create();
void ggl_glsl_enable_shaders(struct ggl_glsl *glsl);
void ggl_glsl_disable_shaders(struct ggl_glsl *glsl);
