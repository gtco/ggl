#include "game.h"
#include "glsl.h"
#include "sprite.h"
#include "texture.h"

float interval = 0.0f;
struct ggl_texture *texture = 0;

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
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	        game->glsl_ = ggl_glsl_create();
            ggl_glsl_init(game->glsl_, "shaders/colorShading.vert", "shaders/colorShading.frag");

            game->sprite_ = ggl_sprite_create();
            ggl_sprite_init(game->sprite_, -0.5f, -0.5f, 1.0f, 1.0f);

            texture = ggl_texture_create();
            ggl_texture_load(texture, "textures/5.png");
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
   
   	ggl_sprite_destroy(game->sprite_);    
    ggl_glsl_destroy(game->glsl_);        

	free(game);
}

void ggl_game_render(struct ggl_game *game)
{
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ggl_glsl_enable_shaders(game->glsl_);

	glActiveTexture(GL_TEXTURE0);    
	glBindTexture(GL_TEXTURE_2D, texture->id_);
	GLint texture_location = ggl_glsl_get_uniform_location(game->glsl_, "my_sampler");
	glUniform1i(texture_location, 0);

	//GLint time_location = ggl_glsl_get_uniform_location(game->glsl_, "time");
	//glUniform1f(time_location, 0);

    ggl_sprite_draw(game->sprite_);

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
	}
}

void ggl_game_update(struct ggl_game * game, uint32_t elapsed)
{
	interval = interval + 0.001f;
}

