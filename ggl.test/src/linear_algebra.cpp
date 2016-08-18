#include "linear_algebra.h"
#include <string.h>
static const double PI = 3.14159265358979323846;

Matrix multiplymat4(const Matrix* m1, const Matrix* m2) {
	Matrix out = IDENTITY_MATRIX;
	unsigned int row, column, row_offset;

	for (row = 0, row_offset = row * 4; row < 4; ++row, row_offset = row * 4)
		for (column = 0; column < 4; ++column)
			out.m[row_offset + column] =
			(m1->m[row_offset + 0] * m2->m[column + 0]) +
			(m1->m[row_offset + 1] * m2->m[column + 4]) +
			(m1->m[row_offset + 2] * m2->m[column + 8]) +
			(m1->m[row_offset + 3] * m2->m[column + 12]);

	return out;
}

Vector4 mulmatvec4(const Matrix* m, const Vector4* v) {
	Vector4 out;
	for (int i = 0; i < 4; ++i) {
		out.m[i] =
			(v->m[0] * m->m[i + 0]) +
			(v->m[1] * m->m[i + 4]) +
			(v->m[2] * m->m[i + 8]) +
			(v->m[3] * m->m[i + 12]);
	}

	return out;
}

void normalizevec4(Vector4* v) {
	float sqr = v->m[0] * v->m[0] + v->m[1] * v->m[1] + v->m[2] * v->m[2];
	if (sqr == 1 || sqr == 0)
		return;
	float invrt = 1.f / sqrt(sqr);
	v->m[0] *= invrt;
	v->m[1] *= invrt;
	v->m[2] *= invrt;
}

float dotvec4(Vector4 v1, Vector4 v2) {
	return v1.m[0] * v2.m[0] + v1.m[1] * v2.m[1] + v1.m[2] * v2.m[2] + v1.m[3] * v2.m[3];
}

Vector4 crossvec4(Vector4 v1, Vector4 v2) {
	Vector4 out = { { 0 } };
	out.m[0] = v1.m[1] * v2.m[2] - v1.m[2] * v2.m[1];
	out.m[1] = v1.m[2] * v2.m[0] - v1.m[0] * v2.m[2];
	out.m[2] = v1.m[0] * v2.m[1] - v1.m[1] * v2.m[0];
	return out;
}
void rotateX(const Matrix* m, float angle) {
	Matrix rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	rotation.m[5] = cosine;
	rotation.m[6] = -sine;
	rotation.m[9] = sine;
	rotation.m[10] = cosine;

	memcpy((void *) m->m, multiplymat4(m, &rotation).m, sizeof(m->m));
}
void rotateY(const Matrix* m, float angle) {
	Matrix rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	rotation.m[0] = cosine;
	rotation.m[8] = sine;
	rotation.m[2] = -sine;
	rotation.m[10] = cosine;

	memcpy((void *) m->m, multiplymat4(m, &rotation).m, sizeof(m->m));
}
void rotateZ(const Matrix* m, float angle) {
	Matrix rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	rotation.m[0] = cosine;
	rotation.m[1] = -sine;
	rotation.m[4] = sine;
	rotation.m[5] = cosine;

	memcpy((void *) m->m, multiplymat4(m, &rotation).m, sizeof(m->m));
}
void scale(const Matrix* m, float x, float y, float z) {
	Matrix scale = IDENTITY_MATRIX;

	scale.m[0] = x;
	scale.m[5] = y;
	scale.m[10] = z;
	scale.m[15] = 1.0f;

	memcpy((void *) m->m, multiplymat4(m, &scale).m, sizeof(m->m));
}

void translate(const Matrix* m, float x, float y, float z) {
	Matrix translation = IDENTITY_MATRIX;

	translation.m[12] = x;
	translation.m[13] = y;
	translation.m[14] = z;
	translation.m[15] = 1.0f;

	memcpy((void *) m->m, multiplymat4(m, &translation).m, sizeof(m->m));
}

Matrix perspective(float fovy, float aspect_ratio, float near_plane, float far_plane) {
	Matrix out = { { 0 } };

	const float
		y_scale = (float)(1 / cos(fovy * PI / 360)),
		x_scale = y_scale / aspect_ratio,
		frustum_length = far_plane - near_plane;

	out.m[0] = x_scale;
	out.m[5] = y_scale;
	out.m[10] = -((far_plane + near_plane) / frustum_length);
	out.m[11] = -1;
	out.m[14] = -((2 * near_plane * far_plane) / frustum_length);

	return out;
}

Matrix orthogonal(float left, float right, float bottom, float top) {
	Matrix out = IDENTITY_MATRIX;
	out.m[0] = 2 / (right - left);
	out.m[5] = 2 / (top - bottom);
	out.m[10] = -1;
	out.m[12] = -(right + left) / (right - left);
	out.m[13] = -(top + bottom) / (top - bottom);

	return out;
}

Matrix lookAt(Vector4 pos, Vector4 dir) {
	Vector4 f = dir;
	normalizevec4(&f);
	Vector4 u = { { 0, 1, 0, 0 } };
	Vector4 s = crossvec4(f, u);
	normalizevec4(&s);
	u = crossvec4(s, f);

	Matrix out = IDENTITY_MATRIX;
	out.m[0] = s.x;
	out.m[4] = s.y;
	out.m[8] = s.z;

	out.m[1] = u.x;
	out.m[5] = u.y;
	out.m[9] = u.z;

	out.m[2] = -f.x;
	out.m[6] = -f.y;
	out.m[10] = -f.z;

	out.m[12] = -dotvec4(s, pos);
	out.m[13] = -dotvec4(u, pos);
	out.m[14] = dotvec4(f, pos);
	return out;
}

/**
 * Multiplies pM1 with pM2, stores the result in pOut, returns pOut
 */
Matrix* multiplymat4_ex(Matrix* pOut, const Matrix* pM1, const Matrix* pM2)
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

	return pOut;
}
