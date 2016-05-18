#include "game.h"
#include "glsl.h"
#include "sprite.h"

Game::Game() : is_running_(false), interval_(0.0f)
{
	//struct ggl_game *game = malloc(sizeof(struct ggl_game));
	//assert(game != NULL);
	//is_running_ = false;
	//glsl_ = NULL;
	//sprite_ = NULL;
	//return game;

}

Game::~Game()
{
	//assert(game != NULL);
	//is_running_ = false;
	//SDL_DestroyWindow(window_);

	//for (int i = 0; i < 5; i++)
	//{
	//	ggl_sprite_destroy(sprite_[i]);
	//}

	//free(sprite_);

	//ggl_glsl_destroy(glsl_);

	//free(game);
}

bool Game::init(const char * title, int xpos, int ypos, int height, int width, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		window_ = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		if (window_ != 0)
		{
#ifdef __APPLE__
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
			gl_context_ = SDL_GL_CreateContext(window_);

			if (gl_context_ == 0)
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

			glsl_ = new Glsl();
			glsl_->init("shaders/colorShading.vert", "shaders/colorShading.frag");

			sprite_ = new Sprite();
			sprite_->init(-0.1f, -0.1f, 0.2f, 0.2f, "textures/4.png");
		}
	}
	else
	{
		return false;
	}

	is_running_ = true;
	return true;

}

void Game::render()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glsl_->enable_shaders();

	glActiveTexture(GL_TEXTURE0);
	GLint texture_location = glsl_->get_uniform_location("my_sampler");
	glUniform1i(texture_location, 0);

	//GLint time_location = ggl_glsl_get_uniform_location(glsl_, "time");
	//glUniform1f(time_location, 0);

	sprite_->draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	glsl_->disable_shaders();

	SDL_GL_SwapWindow(window_);
}

void Game::handle_events()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			is_running_ = false;
			break;
		default:
			break;
		}
	}
}

void Game::update(uint32_t elapsed)
{
	interval_ = interval_ + 0.001f;
}
