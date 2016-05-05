#pragma once

#include "ggl.h"
#include "texture.h"

struct ggl_scene
{
	int id_;
	char name_[32];
};

struct ggl_scene *ggl_scene_create();
void ggl_scene_destroy(struct ggl_scene *scene);
void ggl_scene_draw(struct ggl_scene *scene, SDL_Renderer* renderer);
void ggl_scene_handle_events(struct ggl_scene *scene, SDL_Event event);
void ggl_scene_update(struct ggl_scene *scene, uint32_t elapsed);