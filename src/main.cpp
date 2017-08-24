// Copyright 2017 Alex Frappier Lachapelle
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.


#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glErrors.hpp"


GLFWwindow*   window = nullptr;

int main(int argc, char **argv){
    
    //SDL Init
    if (!glfwInit()){
        std::cout << "Failed to initialize GLFW." << std::endl;
        return -1;
    }
    
    
    //Create Window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(1024, 768, "OpenGLFun", NULL, NULL);
    if (window == nullptr) {
        std::cout << "Failed to create a window." << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    
    //Init GLEW
    glewExperimental = GL_TRUE;
    GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    
    //OpenGL Init
    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    const GLchar* vShaderSrc[] = { "#version 330 core\nlayout(location = 0) in vec3 vertexPos;\nvoid main() { gl_Position.xyz = vertexPos; gl_Position.w = 1.0; }" };
    const GLchar* fShaderSrc[] = { "#version 330 core\nout vec3 frag; void main() { frag = vec3( 1, 0, 0 ); }" };
    
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
        glfwTerminate();
        return -1;
    }
    
    glLinkProgram(programID);
    
    GLint linkSuccess = GL_TRUE;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess != GL_TRUE) {
        std::cout << "Failed to link shader program" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glClearColor(0.f, 0.f, 0.f, 1.f);
    
    GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             0.0f,  1.0f, 0.0f
    };
    
    GLuint VBO;
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,  GL_STATIC_DRAW);
    
    //Main loop
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    do {
    
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(programID);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glDisableVertexAttribArray(0);
        glUseProgram(NULL);
    
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
    
    
    //Deinit
    glDeleteProgram(programID);
    glfwDestroyWindow(window);
    window = nullptr;
    glfwTerminate();
    
    return 0;
}