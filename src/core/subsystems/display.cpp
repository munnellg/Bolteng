#include "subsystems.h"
#include "../logging.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_GLContext glContext;

static int const OPENGL_MAJOR_VERSION = 4;
static int const OPENGL_MINOR_VERSION = 6;

namespace subsystems {
    namespace display {
        int init() {
            LOG_INFO("Initializing display subsystem");

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

            LOG_INFO("Using OpenGL v%d.%d", OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION);

            window = SDL_CreateWindow(
                "OpenGL Tutorial", 
                SDL_WINDOWPOS_CENTERED, 
                SDL_WINDOWPOS_CENTERED, 
                /*settings.window_width*/ 1280, 
                /*settings.window_height*/ 720, 
                /*settings.window_flags |*/ SDL_WINDOW_OPENGL
            );

            if (!window) {
                LOG_ERROR("SDL_CreateWindow: %s", SDL_GetError());
                return 0;
            }

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (!renderer) {
                LOG_ERROR("SDL_CreateRenderer: %s", SDL_GetError());
                return 0;
            }

            glContext = SDL_GL_CreateContext(window);
            if (!glContext) {
                LOG_ERROR("SDL_GL_CreateContext: %s", SDL_GetError());
                return 0;
            }
            
            GLuint err = glewInit();
            if (err != GLEW_OK) {
                LOG_ERROR("glewInit: %s", glewGetString(err));
                return 0;
            }

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            LOG_INFO("Display subsystem initialized");

            return 1;
        }
    
        void swap() {
            SDL_GL_SwapWindow(window);
        }

        void quit() {
            if (glContext) { SDL_GL_DeleteContext(glContext); }
            if (renderer)  { SDL_DestroyRenderer(renderer); }
            if (window)    { SDL_DestroyWindow(window); }
            LOG_INFO("Display subsystem terminated");
        }
    }
}

