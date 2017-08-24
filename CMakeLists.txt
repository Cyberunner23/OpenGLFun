cmake_minimum_required(VERSION 3.8.2)


#------------------------------------------------------------------------------
# Hunter & Project
#------------------------------------------------------------------------------
include("cmake/HunterGate.cmake")

HunterGate(
        URL  "https://github.com/ruslo/hunter/archive/v0.19.72.tar.gz"
        SHA1 "3ed5ea39abf52afab06c77e1b7d7e41e939752f1"
)

project(OpenGLFun)

hunter_add_package(glew)
find_package(glew CONFIG REQUIRED)

hunter_add_package(glfw)
find_package(glfw3 CONFIG REQUIRED)


#------------------------------------------------------------------------------
# Other dependencies
#------------------------------------------------------------------------------

find_package(OpenGL REQUIRED)


#------------------------------------------------------------------------------
# Main files
#------------------------------------------------------------------------------

set(SRCS
        src/main.cpp
)

set(HEADERS
        src/glErrors.hpp
)


#------------------------------------------------------------------------------
# Executable
#------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME}
        glew::glew
        glfw
        OpenGL::GL
)
