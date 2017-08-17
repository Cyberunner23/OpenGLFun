// Copyright 2017 Alex Frappier Lachapelle
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.


#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "glErrors.hpp"

void SDLCrash(std::string msg) {
    std::cout << msg << ": " << SDL_GetError() << std::endl;
    SDL_Quit();
    std::abort();
}

void OGLCheck(std::string msg) {
    
    GLenum error = glGetError();
    if (error == GL_NO_ERROR)
        return;
    
    std::cout << msg << ": " << glError(error) << std::endl;
    SDL_Quit();
    std::abort();
}

SDL_Window*   window = nullptr;
SDL_GLContext glContext;

int main(int argc, char **argv){
    
    //SDL Init
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        SDLCrash("Failed to initialize SDL");
    }
    
    
    //Create Window
    //TODO: Switch to 4.5 once initial tests are done
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    //SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTSEXT_PROFILE_CORE );
    
    window = SDL_CreateWindow( "OpenGLFun", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    if (window == nullptr) {
        SDLCrash("Failed to create the window");
    }
    
    
    //Init OpenGL context
    glContext = SDL_GL_CreateContext(window);
    if (glContext == 0) {
        SDLCrash("Failed to create an OpenGL context");
    }
    
    
    //Setup VSync
    if (SDL_GL_SetSwapInterval(1) < 0) {
        SDLCrash("Failed to setup VSync");
    }
    
    
    //OpenGL Init
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    OGLCheck("Failed to initialize the OpenGL projection matrix");
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    OGLCheck("Error initializing OpenGL modelview matrix");
    
    glClearColor(0.f, 0.f, 0.f, 1.f);
    OGLCheck("Failed to clear the screen");
    
    
    //Main loop
    bool      quit = false;
    SDL_Event event;
    
    do {
        
        //Process events
        while (SDL_PollEvent(&event)) {
            quit = event.type == SDL_QUIT || event.type == SDL_KEYDOWN;
        }
        
        //Render a thing
        glClear( GL_COLOR_BUFFER_BIT );
    
        //Render quad
        glBegin( GL_QUADS );
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
        glEnd();
        SDL_GL_SwapWindow(window);
        
    } while (!quit);
    
    
    //Deinit
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
    
    return 0;
}