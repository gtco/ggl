#include "math2d.h"
#include <string.h>
static const double PI = 3.14159265358979323846;

void ggl_rotateX(const struct ggl_mat4* m, float angle) {
	struct ggl_mat4 rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	rotation.m[5] = cosine;
	rotation.m[6] = -sine;
	rotation.m[9] = sine;
	rotation.m[10] = cosine;

	memcpy((void *) m->m, &rotation.m, sizeof(m->m));
}
void ggl_rotateY(const struct ggl_mat4* m, float angle) {
	struct ggl_mat4 rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	rotation.m[0] = cosine;
	rotation.m[8] = sine;
	rotation.m[2] = -sine;
	rotation.m[10] = cosine;

	memcpy((void *) m->m, &rotation.m, sizeof(m->m));
}

void ggl_scale(const struct ggl_mat4* m, float x, float y, float z) {
	struct ggl_mat4 scale = IDENTITY_MATRIX;

	scale.m[0] = x;
	scale.m[5] = y;
	scale.m[10] = z;
	scale.m[15] = 1.0f;

	memcpy((void *) m->m, &scale.m, sizeof(m->m));
}

void ggl_translate(const struct ggl_mat4* m, float x, float y, float z) {
	struct ggl_mat4 translation = IDENTITY_MATRIX;

	translation.m[12] = x;
	translation.m[13] = y;
	translation.m[14] = z;
	translation.m[15] = 1.0f;

	memcpy((void *) m->m, &translation.m, sizeof(m->m));
}

struct ggl_mat4 ggl_orthogonal(float left, float right, float bottom, float top) {
	struct ggl_mat4 out = IDENTITY_MATRIX;
	out.m[0] = 2 / (right - left);
	out.m[5] = 2 / (top - bottom);
	out.m[10] = -1;
	out.m[12] = -(right + left) / (right - left);
	out.m[13] = -(top + bottom) / (top - bottom);

	return out;
}

/**
 * Multiplies pM1 with pM2, stores the result in pOut, returns pOut
 */
void ggl_multiplymat4(struct ggl_mat4* pOut, const struct ggl_mat4* pM1, const struct ggl_mat4* pM2)
{
	float mat[16];

	const float *m1 = pM1->m, *m2 = pM2->m;

	mat[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
	mat[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
	mat[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
	mat[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

	mat[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
	mat[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
	mat[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
	mat[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

	mat[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
	mat[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
	mat[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
	mat[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

	mat[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
	mat[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
	mat[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
	mat[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];

	memcpy(pOut->m, mat, sizeof(float)*16);
}
