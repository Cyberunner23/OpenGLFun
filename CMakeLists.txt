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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


hunter_add_package(glew)
find_package(glew CONFIG REQUIRED)

hunter_add_package(glfw)
find_package(glfw3 CONFIG REQUIRED)

hunter_add_package(glm)
find_package(glm CONFIG REQUIRED)


#------------------------------------------------------------------------------
# Other dependencies
#------------------------------------------------------------------------------

find_package(OpenGL REQUIRED)


#------------------------------------------------------------------------------
# Main files
#------------------------------------------------------------------------------

set(SRCS
        src/main.cpp
        src/glShaderUtil.cpp
)

set(HEADERS
        src/glShaderUtil.hpp
)


#------------------------------------------------------------------------------
# Assets
#------------------------------------------------------------------------------

#Copy over the shaders
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/shaders)
configure_file(shaders/generic.vert shaders/generic.vert COPYONLY)
configure_file(shaders/generic.frag shaders/generic.frag COPYONLY)


#------------------------------------------------------------------------------
# Executable
#------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME}
        glew::glew
        glfw
        glm
        OpenGL::GL
)
