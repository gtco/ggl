//
//  window.h
//  ggl
//
//  Created by Greg Copeland on 5/15/16.
//  Copyright © 2016 ggl. All rights reserved.
//

#pragma once

#include "ggl.h"

struct ggl_window {
    SDL_Window *window_;
    SDL_Renderer *renderer_;
    SDL_GLContext gl_context_;
};

struct ggl_window *ggl_window_create();
void ggl_window_destroy(struct ggl_window *window);
bool ggl_window_init(struct ggl_window *window, const char* title, int xpos, int ypos, int height, int width, int flags);
void ggl_window_swap(struct ggl_window *window);

