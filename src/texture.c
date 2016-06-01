#include "texture.h"
#include "lodepng.h"

struct ggl_texture *ggl_texture_create()
{
	struct ggl_texture *texture = malloc(sizeof(struct ggl_texture));
	assert(texture != NULL);
	//TODO

	return texture;
}

void ggl_texture_load(struct ggl_texture *texture, const char* filename)
{
	unsigned char* image;
	unsigned width, height;
	unsigned char* png = 0;
	size_t pngsize;

	unsigned error = lodepng_load_file(&png, &pngsize, filename);
	if (!error)
	{
		error = lodepng_decode32(&image, &width, &height, png, pngsize);
	}

	if (error)
	{
		debug("error %u: %s\n", error, lodepng_error_text(error));
	}

	free(png);

	glGenTextures(1, &(texture->id_));
	
	glBindTexture(GL_TEXTURE_2D, texture->id_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	texture->width_ = width;
	texture->height_ = height;

	free(image);
}

void ggl_texture_destroy(struct ggl_texture *texture)
{
	assert(texture != NULL);
	free(texture);
}

