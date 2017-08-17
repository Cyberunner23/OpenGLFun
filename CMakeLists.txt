cmake_minimum_required(VERSION 3.0)


#------------------------------------------------------------------------------
# Hunter & Project
#------------------------------------------------------------------------------
include("cmake/HunterGate.cmake")

HunterGate(
        URL  "https://github.com/ruslo/hunter/archive/v0.19.72.tar.gz"
        SHA1 "3ed5ea39abf52afab06c77e1b7d7e41e939752f1"
)

project(OpenGLFun)

hunter_add_package(SDL2)
find_package(SDL2 REQUIRED)


#------------------------------------------------------------------------------
# Main files
#------------------------------------------------------------------------------

set(SRC_FILES
    src/main.cpp
)


#------------------------------------------------------------------------------
# Executable
#------------------------------------------------------------------------------

add_executable(main ${SRC_FILES})
target_link_libraries(main
        SDL2::SDL2main
        SDL2::SDL2)
