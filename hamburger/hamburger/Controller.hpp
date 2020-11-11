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
    
    int mRightClick;
   
    
    SDL_Event event;
public:
    Controller();
    //update internal values with events
    void pollEvents();
    bool quit;
    void printControl();
    int mLeftClick;
    SDL_Point mPosition;
    
};

#endif /* Controller_hpp */
