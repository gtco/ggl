#include "game.h"

struct ggl_game *ggl_game_create() 
{
	struct ggl_game *game = malloc(sizeof(struct ggl_game));
	assert(game != NULL);
	game->is_running_ = false;
	//TODO

	return game;
}

bool ggl_game_init(struct ggl_game *game, const char* title, int xpos, int ypos, int height, int width, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		game->window_ = SDL_CreateWindow(title, xpos, ypos, height, width,flags);

		if (game->window_ != 0)
		{            
            game->gl_context_ = SDL_GL_CreateContext(game->window_);
            
            if (game->gl_context_ == 0)
            {
                log_err("Failed to create Open GL context");
                return false;
            }
            
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            glClearColor(1.0f, 0.6f, 0.0f, 1.0f);
		}
	}
	else
	{
		return false;
	}

	game->is_running_ = true;
	return true;
}

void ggl_game_destroy(struct ggl_game *game)
{
	assert(game != NULL);
	game->is_running_ = false;
	SDL_DestroyWindow(game->window_);
	SDL_DestroyRenderer(game->renderer_);
	free(game);
}

void ggl_game_render(struct ggl_game *game)
{
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableClientState(GL_COLOR_ARRAY);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0, 0);
    glVertex2f(0, 200);
    glVertex2f(200, 200);
    glEnd();
    
    SDL_GL_SwapWindow(game->window_);
}

void ggl_game_handle_events(struct ggl_game *game)
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			game->is_running_ = false;
			break;
		default:
			break;
		}

		ggl_scene_handler_events(game->current_scene, event);
	}
}

void ggl_game_update(struct ggl_game * game, uint32_t elapsed)
{
	ggl_scene_update(game->current_scene, elapsed);
}
