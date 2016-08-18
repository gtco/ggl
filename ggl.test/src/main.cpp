#include <stdio.h>

#include "camera2d.h"
#include "math2d.h"
#include "kazmath.h"

#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
// All 16 valus in a 4x4 matrix must match
#define GOAL	16

int compare_glm(glm::mat4 gl4, kmMat4 km4);
int compare_la(struct ggl_mat4 gl4, kmMat4 km4);
void test_km(int screen_width, int screen_height, glm::vec2 position);
void test_la(int screen_width, int screen_height, glm::vec2 position);

int main(int argc, char** argv)
{
	int screen_width = 640;
	int screen_height = 480;
	glm::vec2 position(0.0f, 0.0f);
	float scale = 1.0f;

	test_km(screen_width, screen_height, position);
	test_la(screen_width, screen_height, position);

	getchar();
}

void test_la(int screen_width, int screen_height, glm::vec2 position)
{
	struct ggl_mat4 ortho = ggl_orthogonal(0.0f, (float)screen_width, 0.0f, (float)screen_height);
	struct ggl_mat4 camera = IDENTITY_MATRIX;
	struct ggl_mat4 tmp = IDENTITY_MATRIX;
	ggl_translate(&tmp, -position.x + (screen_width / 2), -position.y + (screen_height / 2), 0.0f);
	ggl_multiplymat4(&camera, &ortho, &tmp);
	tmp = IDENTITY_MATRIX;
	ggl_scale(&tmp, 1.0f, 1.0f, 0.0f);
	ggl_multiplymat4(&camera, &camera, &tmp);

	kmMat4 kmOrtho;
	kmMat4 kmCamera;
	kmMat4 kmTmp;
	kmMat4OrthographicProjection2(&kmOrtho, 0.0f, (float)screen_width, 0.0f, (float)screen_height);
	kmMat4Identity(&kmCamera);
	kmMat4Translation(&kmTmp, -position.x + (screen_width / 2), -position.y + (screen_height / 2), 0.0f);
	kmMat4Multiply(&kmCamera, &kmOrtho, &kmTmp);
	kmMat4Scaling(&kmTmp, 1.0f, 1.0f, 0.0f);
	kmMat4Multiply(&kmCamera, &kmCamera, &kmTmp);

	bool b = (compare_la(ortho, kmOrtho) == GOAL) && (compare_la(camera, kmCamera) == GOAL);
	debug("calculations for la and kazmath match : %s", b ? "true" : "false");
}

void test_km(int screen_width, int screen_height, glm::vec2 position)
{
	Camera2d c;
	c.init(screen_height, screen_width);
	c.set_position(position);
	c.update();

	kmMat4 kmOrtho;
	kmMat4 kmCamera;
	kmMat4 kmTmp;
	kmMat4OrthographicProjection2(&kmOrtho, 0.0f, (float)screen_width, 0.0f, (float)screen_height);
	kmMat4Identity(&kmCamera);
	kmMat4Translation(&kmTmp, -position.x + (screen_width / 2), -position.y + (screen_height / 2), 0.0f);
	kmMat4Multiply(&kmCamera, &kmOrtho, &kmTmp);
	kmMat4Scaling(&kmTmp, 1.0f, 1.0f, 0.0f);
	kmMat4Multiply(&kmCamera, &kmCamera, &kmTmp);

	// Move

	glm::vec2 new_position = glm::vec2(1.0f, -1.0f);
	c.set_position(new_position);
//	c.set_scale(1.5f);
	c.update();

	kmMat4Translation(&kmTmp, -new_position.x + (screen_width / 2), -new_position.y + (screen_height / 2), 0.0f);
	kmMat4Multiply(&kmCamera, &kmOrtho, &kmTmp);
//	kmMat4Scaling(&kmTmp, 1.5f, 1.5f, 0.0f);
//	kmMat4Multiply(&kmCamera, &kmCamera, &kmTmp);


	bool b = (compare_glm(c.get_ortho_matrix(), kmOrtho) == GOAL) && (compare_glm(c.get_camera_matrix(), kmCamera) == GOAL);
	debug("calculations for glm and kazmath match : %s", b ? "true" : "false");
}

int compare_glm(glm::mat4 gl4, kmMat4 km4)
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

int compare_la(struct ggl_mat4 gl4, kmMat4 km4)
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