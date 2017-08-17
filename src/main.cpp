// Copyright 2017 Alex Frappier Lachapelle
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.


#include<iostream>
#include<SDL2/SDL.h>

int main(int argc, char **argv){
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "Error while initializing SDL: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }
    
    SDL_Quit();
    
    return 0;
}