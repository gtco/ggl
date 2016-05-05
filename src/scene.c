#include "scene.h"

struct ggl_scene *ggl_scene_create()
{
	struct ggl_scene *scene = malloc(sizeof(struct ggl_scene));
	assert(scene != NULL);
	scene->id = 1;
	strcpy(scene->name, "default");

	return scene;
}

void ggl_scene_destroy(struct ggl_scene *scene)
{
	assert(scene != NULL);
	free(scene);
}

void ggl_scene_draw(struct ggl_scene * scene, SDL_Renderer * renderer)
{
}

void ggl_scene_handle_events(struct ggl_scene * scene, SDL_Event event)
{
}

void ggl_scene_update(struct ggl_scene *scene, uint32_t elapsed)
{
}