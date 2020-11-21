//
//  Controller.hpp
//  hamburger
//
//  Created by Ali Hamdani on 11/3/20.
//

#ifndef Controller_hpp
#define Controller_hpp

#include <stdio.h>
#include "SDL.h"
#include <string>

class Controller{
private:
    int up;
    int down;
    int left;
    int right;
    int touch;
    int click;
    
    SDL_Event event;
public:
    Controller();
    //update internal values with events
    void pollEvents(SDL_DisplayMode* gMode);
    bool quit;
    void printControl();
    SDL_Point mPosition;
    SDL_Point touchPosition;
    
};

#endif /* Controller_hpp */
