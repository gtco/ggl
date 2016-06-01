#include "game.h"
#include "glsl.h"
#include "sprite.h"

float interval = 0.0f;

struct ggl_game *ggl_game_create() 
{
	struct ggl_game *game = malloc(sizeof(struct ggl_game));
	assert(game != NULL);
	game->is_running_ = false;
    game->glsl_ = NULL;
    game->sprite_ = NULL;
	return game;
}

bool ggl_game_init(struct ggl_game *game, const char* title, int xpos, int ypos, int height, int width, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		game->window_ = SDL_CreateWindow(title, xpos, ypos, height, width,flags);

		if (game->window_ != 0)
		{
#ifdef __APPLE__
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
            game->gl_context_ = SDL_GL_CreateContext(game->window_);
            
            if (game->gl_context_ == 0)
            {
				const char* err = SDL_GetError();
                log_err("Failed to create Open GL context %s", err);
                return false;
            }

#ifdef __APPLE__
            GLuint vertexArrayID;
            glGenVertexArrays(1, &vertexArrayID);
            glBindVertexArray(vertexArrayID);
#endif

 #ifdef _WIN32
			//Set up glew (optional but recommended)
			GLenum error = glewInit();
			if (error != GLEW_OK) {
				log_err("Could not initialize glew!");
			}
#endif
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	        game->glsl_ = ggl_glsl_create();
            ggl_glsl_init(game->glsl_, "shaders/colorShading.vert", "shaders/colorShading.frag");

			game->sprite_ = (struct ggl_sprite **) calloc(5, sizeof(struct ggl_sprite *));
            game->sprite_[0] = ggl_sprite_create();
            ggl_sprite_init(game->sprite_[0], 0.0f, 0.0f, 0.1f, 0.1f, "textures/1.png");

			game->sprite_[1] = ggl_sprite_create();
			ggl_sprite_init(game->sprite_[1], -0.75f, 0.75f, 0.1f, 0.1f, "textures/2.png");

			game->sprite_[2] = ggl_sprite_create();
			ggl_sprite_init(game->sprite_[2], -0.75f, -0.75f, 0.1f, 0.1f, "textures/3.png");

			game->sprite_[3] = ggl_sprite_create();
			ggl_sprite_init(game->sprite_[3], 0.75f, 0.75f, 0.1f, 0.1f, "textures/4.png");

			game->sprite_[4] = ggl_sprite_create();
			ggl_sprite_init(game->sprite_[4], 0.75f, -0.75f, 0.1f, 0.1f, "textures/5.png");
		}
	}
	else
	{
		return false;
	}

	game->current_scene_ = ggl_scene_create();
	game->is_running_ = true;
	return true;
}

void ggl_game_destroy(struct ggl_game *game)
{
	assert(game != NULL);
	game->is_running_ = false;
	ggl_scene_destroy(game->current_scene_);
	SDL_DestroyWindow(game->window_);
   
	for (int i = 0; i < 5; i++)
	{
		ggl_sprite_destroy(game->sprite_[i]);
	}

	free(game->sprite_);

    ggl_glsl_destroy(game->glsl_);        

	free(game);
}

void ggl_game_render(struct ggl_game *game)
{
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ggl_glsl_enable_shaders(game->glsl_);

	glActiveTexture(GL_TEXTURE0);    
	GLint texture_location = ggl_glsl_get_uniform_location(game->glsl_, "my_sampler");
	glUniform1i(texture_location, 0);

	//GLint time_location = ggl_glsl_get_uniform_location(game->glsl_, "time");
	//glUniform1f(time_location, 0);

	for (int i = 0; i < 5; i++)
	{
		ggl_sprite_draw(game->sprite_[i]);
	}

	glBindTexture(GL_TEXTURE_2D, 0);    
	ggl_glsl_disable_shaders(game->glsl_);

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
//		ggl_scene_handle_events(game->current_scene_, event);
	}
}

void ggl_game_update(struct ggl_game * game, uint32_t elapsed)
{
	interval = interval + 0.001f;
//	ggl_scene_update(game->current_scene_, elapsed);
}

