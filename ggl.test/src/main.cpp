#include <stdio.h>

#include "camera2d.h"
#include "linear_algebra.h"
#include "kazmath.h"

#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

int compare(glm::mat4 gl4, kmMat4 km4);
int compare_la(Matrix gl4, kmMat4 km4);
void test_km();
void test_la();

int main(int argc, char** argv)
{
	test_km();
	test_la();
	getchar();
}

void test_la()
{
	int screen_width = 640;
	int screen_height = 480;
	glm::vec2 position(0.0f, 0.0f);

	kmMat4 kom;
	kmMat4 tmp;
	kmMat4 com;

	kmMat4OrthographicProjection2(&kom, 0.0f, (float)screen_width, 0.0f, (float)screen_height);
	kmMat4Identity(&com);
	kmMat4Translation(&tmp, -position.x + (screen_width / 2), -position.y + (screen_height / 2), 0.0f);
	kmMat4Multiply(&com, &kom, &tmp);
	kmMat4Scaling(&tmp, 1.0f, 1.0f, 0.0f);
	kmMat4Multiply(&com, &com, &tmp);

	Matrix ortho = orthogonal(0.0f, (float)screen_width, 0.0f, (float)screen_height);
	Matrix mtmp = IDENTITY_MATRIX;
	Matrix camera = IDENTITY_MATRIX;
	translate(&mtmp, -position.x + (screen_width / 2), -position.y + (screen_height / 2), 0.0f);
	multiplymat4_ex(&camera, &ortho, &mtmp);
	mtmp = IDENTITY_MATRIX;
	scale(&mtmp, 1.0f, 1.0f, 0.0f);
	multiplymat4_ex(&camera, &camera, &mtmp);
	
	int match_ortho = compare_la(ortho, kom);
	int match_camera = compare_la(camera, com);
	bool b = (match_ortho == 16) && (match_camera == 16);
	debug("calculations for la and kazmath match : %s", b ? "true" : "false");
}

void test_km()
{
	Camera2d c;

	int screen_width = 640;
	int screen_height = 480;

	c.init(screen_height, screen_width);
	glm::vec2 position(0.0f, 0.0f);

	Matrix om = orthogonal(0.0f, (float)screen_width, 0.0f, (float)screen_height);
	kmMat4 kom;
	kmMat4OrthographicProjection2(&kom, 0.0f, (float)screen_width, 0.0f, (float)screen_height);

	c.set_position(position);
	c.update();

	kmMat4 tmp;
	kmMat4 com;
	kmMat4Identity(&com);
	kmMat4Translation(&tmp, -position.x + (screen_width / 2), -position.y + (screen_height / 2), 0.0f);
	kmMat4Multiply(&com, &kom, &tmp);
	kmMat4Scaling(&tmp, 1.0f, 1.0f, 0.0f);
	kmMat4Multiply(&com, &com, &tmp);

	int match_ortho = compare(c.get_ortho_matrix(), kom);
	int match_camera = compare(c.get_camera_matrix(), com);
	bool b = (match_ortho == 16) && (match_camera == 16);
	debug("calculations for glm and kazmath match : %s", b ? "true" : "false");
}

int compare(glm::mat4 gl4, kmMat4 km4)
{
	int matches = 0;
	int c = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float g = gl4[i][j];
			float k = (float)km4.mat[c];

			if (g == k)
			{
				matches++;
			}

			c++;
		}
	}

	return matches;
}

int compare_la(Matrix gl4, kmMat4 km4)
{
	int matches = 0;
	int c = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float g = gl4.m[c];
			float k = (float)km4.mat[c];

			if (g == k)
			{
				matches++;
			}

			c++;
		}
	}

	return matches;
}