// Copyright 2017 Alex Frappier Lachapelle
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.


#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glCamera.hpp"
#include "glShaderUtil.hpp"


GLFWwindow*  window;
unsigned int screenWidth  = 1024;
unsigned int screenHeight = 768;

glCamera  camera;
glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;
glm::mat4 MVP;

const float camSpeedFactor   = 0.05;
const float mouseSensitivity = 1.0;

void windowSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    screenWidth  = (unsigned int)width;
    screenHeight = (unsigned int)height;
    projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / screenHeight, 1.0f, 100.0f);
}

void handleKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))  {
        camera.zVirtPos += camSpeedFactor;
    } else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera.zVirtPos -= camSpeedFactor;
    } else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera.xVirtPos += camSpeedFactor;
    } else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera.xVirtPos -= camSpeedFactor;
    } else if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera.yVirtPos += camSpeedFactor;
    } else if (key == GLFW_KEY_LEFT_SHIFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera.yVirtPos -= camSpeedFactor;
    }

    view = camera.computeViewMat();
}

int main(int argc, char **argv){
    
    
    //GLFW Init
    if (!glfwInit()){
        std::cout << "Failed to initialize GLFW." << std::endl;
        return -1;
    }
    
    
    //Create Window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(screenWidth, screenHeight, "OpenGLFun", NULL, NULL);
    if (window == nullptr) {
        std::cout << "Failed to create a window." << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwSetKeyCallback(window, handleKeyboardInput);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
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
    
    GLuint      programID;
    std::string shaderErr = setupGenericShaders(programID, "shaders/generic.vert", "shaders/generic.frag");
    if (shaderErr != "") {
        std::cout << shaderErr << std::endl;
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
    camera.zVirtPos = -3.0f;
    
    model      = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view       = camera.computeViewMat();
    projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / screenHeight, 1.0f, 100.0f);
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);
    do {
        
        MVP   = projection * view * model;
        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        glUseProgram(programID);
        glEnableVertexAttribArray(0);
        
        GLint MVPLocation = glGetUniformLocation(programID, "MVP");
        glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glDisableVertexAttribArray(0);
        glUseProgram((GLuint)NULL);
    
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
