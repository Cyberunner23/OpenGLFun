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
    
    glm::vec3 camPos;
    glm::vec3 camRot;
    
    glCamera() : camPos(0.0f, 0.0f, 0.0f),
                 camRot(0.0f, 0.0f, 0.0f) {}
    
    glm::mat4 computeViewMat() {
        
        glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(camRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(camRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(camRot.z), glm::vec3(0.0f, 0.0f, 1.0f));
        
        glm::mat4 rotate = rotZ * rotX * rotY;
    
        glm::mat4 translate = glm::mat4(1.0f);
        translate = glm::translate(translate, -camPos);
    
        return rotate * translate;
    }

};
