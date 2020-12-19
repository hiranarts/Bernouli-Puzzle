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
    
    SDL_Event event;
public:
    //variables
    SDL_Point mPosition;
    SDL_Point touchPosition;
    int up;
    int down;
    int left;
    int right;
    int touch;
    int click;
    
    Controller();
    //update internal values with events
    void pollEvents(SDL_DisplayMode* gMode);
    bool quit;
    void printControl();
    
    
    
};

#endif /* Controller_hpp */
