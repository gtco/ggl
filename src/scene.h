#pragma once

#include "ggl.h"

struct ggl_scene
{
	int id;
	char name[32];
};

void ggl_scene_draw(struct ggl_scene *scene, SDL_Renderer* renderer);
void ggl_scene_handler_events(struct ggl_scene *scene, SDL_Event event);
void ggl_scene_update(struct ggl_scene *scene, uint32_t elapsed);