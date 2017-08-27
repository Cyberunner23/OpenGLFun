// Copyright 2017 Alex Frappier Lachapelle
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.

#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct glCamera {

    float xVirtPos = 0.0f;
    float yVirtPos = 0.0f;
    float zVirtPos = 0.0f;
    
    float xRotation = 0;
    float yRotation = 0;
    float zRotation = 0;
    
    glm::mat4 computeViewMat() {
        
        glm::mat4 view;
        
        view = glm::translate(view, glm::vec3(-xVirtPos, -yVirtPos, -zVirtPos));
        view = glm::rotate(view, glm::radians(xRotation), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::rotate(view, glm::radians(yRotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::rotate(view, glm::radians(zRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    
        return view;
        
    }

};
