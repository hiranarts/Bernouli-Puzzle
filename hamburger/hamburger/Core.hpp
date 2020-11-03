//
//  Core.hpp
//  hamburger
//
//  Created by Ali Hamdani on 11/2/20.
//

#ifndef Core_hpp
#define Core_hpp

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"
#include <string>

class Core{
private:
    SDL_DisplayMode DEVICE;
        
    
    //Private methods
    bool init();
    bool initWindowAndRenderer();
    
public:
    SDL_Window* GAME_WINDOW;
    SDL_Renderer* RENDERER;

    Core();

};

#endif /* Core_hpp */
