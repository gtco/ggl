#include "game.h"
#include "glsl.h"
#include "sprite.h"

Game::Game() : is_running_(false), interval_(0.0f)
{
}

Game::~Game()
{
}

bool Game::init(const char * title, int xpos, int ypos, int height, int width, int flags)
{
	camera_.init(width, height);

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		if (window_.init(title, xpos, ypos, height, width, flags))
		{
			glsl_.init("shaders/colorShading.vert", "shaders/colorShading.frag");
			player_.init(-16.0f, -32.0f, 32.0f, 32.0f, "textures/5.png");
			enemy_.init(-16.0f, 32.0f, 32.0f, 32.0f, "textures/1.png");
		}
	}
	else
	{
		return false;
	}

	is_running_ = true;
	return true;
}

void Game::draw()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glsl_.enable_shaders();

	glActiveTexture(GL_TEXTURE0);
	GLint texture_location = glsl_.get_uniform_location("my_sampler");
	glUniform1i(texture_location, 0);

	// Set the camera matrix
	GLint p_location = glsl_.get_uniform_location("P");
	glm::mat4 camera_matrix = camera_.get_camera_matrix();
	glUniformMatrix4fv(p_location, 1, GL_FALSE, &(camera_matrix[0][0]));

	enemy_.draw();
	player_.draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	glsl_.disable_shaders();

	window_.swap();
}

void Game::handle_events()
{
    float CAMERA_SPEED = 20.0f;
    float SCALE_SPEED = 0.1f;
    
	SDL_Event evt;
	if (SDL_PollEvent(&evt))
	{
		switch (evt.type)
		{
		case SDL_QUIT:
			is_running_ = false;
			break;
		case SDL_KEYDOWN:
			switch (evt.key.keysym.sym)
			{
			case SDLK_w:
				camera_.set_position(camera_.get_position() + glm::vec2(0.0f, CAMERA_SPEED));
				break;
			case SDLK_s:
				camera_.set_position(camera_.get_position() + glm::vec2(0.0f, -CAMERA_SPEED));
				break;
			case SDLK_a:
				camera_.set_position(camera_.get_position() + glm::vec2(-CAMERA_SPEED, 0.0f));
				break;
			case SDLK_d:
				camera_.set_position(camera_.get_position() + glm::vec2(CAMERA_SPEED, 0.0f));
				break;
			case SDLK_q:
				camera_.set_scale(camera_.get_scale() + SCALE_SPEED);
				break;
			case SDLK_e:
				camera_.set_scale(camera_.get_scale() - SCALE_SPEED);
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Game::update(uint32_t elapsed)
{
	camera_.update();
	interval_ = interval_ + 0.001f;
}
