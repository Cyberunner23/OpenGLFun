// Copyright 2017 Alex Frappier Lachapelle
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.


#include <iostream>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "glErrors.hpp"

void SDLCrash(std::string msg) {
    std::cout << msg << ": " << SDL_GetError() << std::endl;
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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,  SDL_GL_CONTEXT_PROFILE_CORE);
    
    window = SDL_CreateWindow("OpenGLFun", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDLCrash("Failed to create the window");
    }
    
    
    //Init OpenGL context
    glContext = SDL_GL_CreateContext(window);
    if (glContext == 0) {
        SDLCrash("Failed to create an OpenGL context");
    }
    
    
    //Init GLEW
    glewExperimental = GL_TRUE;
    GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        SDL_Quit();
        std::abort();
    }
    
    
    //Setup VSync
    if (SDL_GL_SetSwapInterval(1) < 0) {
        SDLCrash("Failed to setup VSync");
    }
    
    
    //OpenGL Init
    
    const GLchar* vShaderSrc[] = { "#version 140\nin vec2 vertexPos; void main() { gl_Position = vec4( vertexPos.x, vertexPos.y, 0, 1 ); }" };
    const GLchar* fShaderSrc[] = { "#version 140\nout vec4 frag; void main() { frag = vec4( 1.0, 1.0, 1.0, 1.0 ); }" };
    
    GLuint programID       = glCreateProgram();
    GLuint vShader         = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader         = glCreateShader(GL_FRAGMENT_SHADER);
    GLint  vShaderCompiled = GL_FALSE;
    GLint  fShaderCompiled = GL_FALSE;
    
    glShaderSource(vShader, 1, vShaderSrc, NULL);
    glShaderSource(fShader, 1, fShaderSrc, NULL);
    
    glCompileShader(vShader);
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vShaderCompiled);
    glAttachShader(programID, vShader);
   
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fShaderCompiled);
    glAttachShader(programID, fShader);
    
    if (vShaderCompiled != GL_TRUE || fShaderCompiled != GL_TRUE) {
        //I'll check what the error is when something messes up.
        std::cout << "Failed to compile a shader" << std::endl;
        SDL_Quit();
        std::abort();
    }
    
    glLinkProgram(programID);
    
    GLint linkSuccess = GL_TRUE;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess != GL_TRUE) {
        std::cout << "Failed to link shader program" << std::endl;
        SDL_Quit();
        std::abort();
    }
    
    GLint vertexPosLoc = glGetAttribLocation(programID, "vertexPos");
    if (vertexPosLoc == -1) {
        std::cout << "vertexPos is an invalid variable (in the shader)" << std::endl;
        SDL_Quit();
        std::abort();
    }
    
    glClearColor(0.f, 0.f, 0.f, 1.f);
    
    GLfloat vertices[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f
    };
    
    GLuint indexData[] = {0, 1, 2, 3};
    
    GLuint VBO;
    GLuint IBO;
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertices,  GL_STATIC_DRAW);
    
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
    
    
    //Main loop
    bool      quit = false;
    SDL_Event event;
    
    do {
        
        //Process events
        while (SDL_PollEvent(&event)) {
            if ((quit = event.type == SDL_QUIT || event.type == SDL_KEYDOWN)) break;
        }
    
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(programID);
        glEnableVertexAttribArray(vertexPosLoc);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(vertexPosLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
        
        glDisableVertexAttribArray(vertexPosLoc);
        glUseProgram(NULL);
    
        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
        
    } while (!quit);
    
    
    //Deinit
    glDeleteProgram(programID);
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
    
    return 0;
}