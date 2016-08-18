#pragma once
#include <math.h>

struct ggl_mat4 {
	float m[16];
};

union ggl_vec4 {
	float m[4];
	struct {
		float x, y, z, w;
	};
};

static const struct ggl_mat4 IDENTITY_MATRIX = {{ 
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
}};

#ifdef __cplusplus
extern "C" {
#endif

	void ggl_rotateX(const struct ggl_mat4* m, float angle);
	void ggl_rotateY(const struct ggl_mat4* m, float angle);
	void ggl_scale(const struct ggl_mat4* m, float x, float y, float z);
	void ggl_translate(const struct ggl_mat4* m, float x, float y, float z);
	struct ggl_mat4 ggl_orthogonal(float left, float right, float bottom, float top);
	void ggl_multiplymat4(struct ggl_mat4* result, const struct ggl_mat4* m1, const struct ggl_mat4* m2);

#ifdef __cplusplus
}
#endif


