// Copyright 2017 Alex Frappier Lachapelle
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.

#include "glShaderUtil.hpp"


std::string linkShaders(GLuint &programID) {
    
    GLint linkSuccess = GL_TRUE;
    
    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess != GL_TRUE) {
        
        std::string logMsg;
        GLint       logLength = 0;
    
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
        logMsg.reserve((GLuint)logLength + 1);
        glGetProgramInfoLog(programID, logLength, NULL, &logMsg[0]);
    
        return logMsg;
    }
    
    return "";
    
}


std::string setupGenericShaders(GLuint &programID, const char* vertFileName, const char* fragFileName) {
    
    GLuint vShaderID;
    GLuint fShaderID;
    std::string shaderErr;
    
    programID = glCreateProgram();
    
    shaderErr = loadShader<GL_VERTEX_SHADER>(vShaderID, vertFileName);
    if (shaderErr != "")
        return "Failed to compile vertex shader: " + shaderErr;
    
    shaderErr = loadShader<GL_FRAGMENT_SHADER>(fShaderID, fragFileName);
    if (shaderErr != "")
        return "Failed to compile fragment shader: " + shaderErr;
    
    glAttachShader(programID, vShaderID);
    glAttachShader(programID, fShaderID);
    
    shaderErr = linkShaders(programID);
    if (shaderErr != "")
        return "Failed to link shader program: " + shaderErr;
    
    glDetachShader(programID, vShaderID);
    glDetachShader(programID, fShaderID);
    glDeleteShader(vShaderID);
    glDeleteShader(fShaderID);
    
    return "";
}
