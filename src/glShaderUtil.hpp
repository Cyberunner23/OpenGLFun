// Copyright 2017 Alex Frappier Lachapelle
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.


#pragma once

#include <fstream>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "GL/glew.h"



template<GLenum shaderType>
std::string loadShader(GLuint &shaderID, const char* fileName) {
    
    std::ifstream  file(fileName);
    std::streampos fileSize;
    
    //Read file
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    if (fileSize == 0) {
        file.close();
        return "Shader file is empty, most definitely is invalid.";
    }
    
    std::string shaderData;
    const char* shaderDataPtr;
    shaderData.reserve(fileSize);
    shaderData.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    shaderDataPtr = shaderData.c_str();
    
    
    //Compile shader
    GLint shaderCompiled = GL_FALSE;
    shaderID = glCreateShader(shaderType);
    
    glShaderSource(shaderID, 1, &shaderDataPtr,NULL);
    glCompileShader(shaderID);
    
    //Check for errors
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
    if (shaderCompiled != GL_TRUE) {
        
        std::string logMsg;
        GLint       logLength = 0;
        
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
        logMsg.reserve((GLuint)logLength + 1);
        glGetShaderInfoLog(shaderID, logLength, NULL, &logMsg[0]);
        
        return logMsg;
    }
    
    return "";
}

std::string linkShaders(GLuint &programID);


std::string setupGenericShaders(GLuint &ProgramID, const char* vertFileName, const char* fragFileName);
