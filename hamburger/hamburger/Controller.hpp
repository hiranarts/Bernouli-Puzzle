//
//  Controller.hpp
//  hamburger
//
//  Created by Ali Hamdani on 11/3/20.
//

#ifndef Controller_hpp
#define Controller_hpp

#include <stdio.h>
#include "SDL2/SDL.h"
#include <string>

class Controller{
private:
    int up;
    int down;
    int left;
    int right;
    
    int mLeftClick;
    int mRightClick;
    SDL_Point mPosition;
    
    SDL_Event event;
public:
    Controller();
    //update internal values with events
    void pollEvents();
    bool quit;
    void printControl();

    
};

#endif /* Controller_hpp */
