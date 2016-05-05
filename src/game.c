#include "game.h"
#include "glsl.h"

struct ggl_sprite *sprite = 0;
struct ggl_glsl *glsl = 0;

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
            
            sprite = ggl_sprite_create();
            ggl_sprite_init(sprite, -1.0f, -1.0f, 1.0f, 1.0f);
            
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            glClearColor(1.0f, 0.6f, 0.0f, 1.0f);
            
            glsl = malloc(sizeof(struct ggl_glsl)); ;
            ggl_glsl_compile_shaders(glsl, "shaders/colorShading.vert", "shaders/colorShading.frag");
            ggl_glsl_bind_attribute(glsl);
            ggl_glsl_link_shaders(glsl);
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
	free(game);
}

void ggl_game_render(struct ggl_game *game)
{
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(glsl->program_id);
    glEnableVertexAttribArray(0);
    
    ggl_sprite_draw(sprite);
    
    glUseProgram(0);
    glDisableVertexAttribArray(0);
    
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

struct ggl_sprite *ggl_sprite_create()
{
    struct ggl_sprite *sprite = malloc(sizeof(struct ggl_sprite));
    assert(sprite != NULL);

    sprite->x = 0;
    sprite->y = 0;
    sprite->height = 0;
    sprite->width = 0;
    sprite->vbo_id = 0;
    
    return sprite;
    
}

bool ggl_sprite_init(struct ggl_sprite *sprite, float x, float y, float height, float width)
{
    sprite->x = x;
    sprite->y = y;
    sprite->height = height;
    sprite->width = width;
    
    if (sprite->vbo_id == 0)
    {
        glGenBuffers(1, &sprite->vbo_id);
    }
    
    // Quad : 2 Triangles (3 vertices per triangle) = 6
    // x and y coord = 2
    float vertex_data[12];
    
    // top right
    vertex_data[0] = x + width;
    vertex_data[1] = y + height;
    // top left
    vertex_data[2] = x ;
    vertex_data[3] = y + height;
    // bottom left
    vertex_data[4] = x;
    vertex_data[5] = y;
    // 2nd triangle
    vertex_data[6] = x;
    vertex_data[7] = y;
    // bottom right
    vertex_data[8] = x + width;
    vertex_data[9] = y;
    
    vertex_data[10] = x + width;
    vertex_data[11] = y + height;
    
    glBindBuffer(GL_ARRAY_BUFFER, sprite->vbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    return true;
}

void ggl_sprite_draw(struct ggl_sprite *sprite)
{
    glBindBuffer(GL_ARRAY_BUFFER, sprite->vbo_id);
    
    glEnableVertexAttribArray(0);
    
    // 2 = elements (x,y)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    // 6 = # of vertices
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ggl_sprite_destroy(struct ggl_sprite *sprite)
{
    if (sprite->vbo_id != 0)
    {
        glDeleteBuffers(1, &sprite->vbo_id);
    }
}
