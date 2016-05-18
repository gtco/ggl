//
//  window.c
//  ggl
//
//  Created by Greg Copeland on 5/15/16.
//  Copyright © 2016 ggl. All rights reserved.
//

#include "window.h"


struct ggl_window *ggl_window_create()
{
    struct ggl_window *window = malloc(sizeof(struct ggl_window));
    assert(window != NULL);
    return window;
}

void ggl_window_destroy(struct ggl_window * window)
{
    assert(window != NULL);

    SDL_DestroyWindow(window->window_);
    
    free(window);
}

void ggl_window_swap(struct ggl_window *window)
{
    SDL_GL_SwapWindow(window->window_);
}

bool ggl_window_init(struct ggl_window *window, const char* title, int xpos, int ypos, int height, int width, int flags)
{
    window->window_ = SDL_CreateWindow(title, xpos, ypos, height, width,flags);
    
    if (window->window_ != 0)
    {
#ifdef __APPLE__
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        
        window->gl_context_ = SDL_GL_CreateContext(window->window_);
        
        if (window->gl_context_ == 0)
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
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        
        // Set VSYNC on(1) or off(1)
        SDL_GL_SetSwapInterval(0);
        
        debug("GL Version [%s]", glGetString(GL_VERSION));
        
        return true;
    }
    else
    {
        // failed to create window
        return false;
    }
}
