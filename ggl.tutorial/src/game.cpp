#include "game.h"
#include "glsl.h"
#include "sprite.h"
#include "texture.h"

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
			sprite_batch_.init();
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

	static Texture player_texture_;
	player_texture_.load("textures/5.png");
	static Texture enemy_texture_;
	enemy_texture_.load("textures/1.png");

	struct ggl_color color;
	color.r = color.g = color.b = color.a = 255;

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	sprite_batch_.begin();

	sprite_batch_.draw(pos - glm::vec4(55.0f, 0.0f, 0.0f, 0.0f), uv, 0, player_texture_.get_id(), color);
	sprite_batch_.draw(pos + glm::vec4(55.0f, 0.0f, 0.0f, 0.0f), uv, 0, enemy_texture_.get_id(), color);

	sprite_batch_.end();
	sprite_batch_.render_batch();

	glBindTexture(GL_TEXTURE_2D, 0);
	glsl_.disable_shaders();

	window_.swap();
}

void Game::handle_events()
{
    float CAMERA_SPEED = 0.7f;
    float SCALE_SPEED = 0.005f;
    
	SDL_Event evt;
	if (SDL_PollEvent(&evt))
	{
		switch (evt.type)
		{
		case SDL_QUIT:
			is_running_ = false;
			break;
		case SDL_KEYDOWN:
			ggl_inputmanager_press_key(evt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			ggl_inputmanager_release_key(evt.key.keysym.sym);
			break;
		default:
			break;
		}
	}

	if (ggl_inputmanager_is_key_pressed(SDLK_w))
	{
		camera_.set_position(camera_.get_position() + glm::vec2(0.0f, -CAMERA_SPEED));
	}
	if (ggl_inputmanager_is_key_pressed(SDLK_s))
	{
		camera_.set_position(camera_.get_position() + glm::vec2(0.0f, CAMERA_SPEED));
	}
	if (ggl_inputmanager_is_key_pressed(SDLK_a))
	{
		camera_.set_position(camera_.get_position() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}
	if (ggl_inputmanager_is_key_pressed(SDLK_d))
	{
		camera_.set_position(camera_.get_position() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
	if (ggl_inputmanager_is_key_pressed(SDLK_q))
	{
		camera_.set_scale(camera_.get_scale() + SCALE_SPEED);
	}
	if (ggl_inputmanager_is_key_pressed(SDLK_e))
	{
		camera_.set_scale(camera_.get_scale() - SCALE_SPEED);
	}
}

void Game::update(uint32_t elapsed)
{
	camera_.update();
}
