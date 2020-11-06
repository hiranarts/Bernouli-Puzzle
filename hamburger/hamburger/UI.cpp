//
//  UI.cpp
//  hamburger
//
//  Created by Ali Hamdani on 11/5/20.
//

#include "UI.hpp"
//first use case is the home screen
UI::UI(int x, int y, int width, int height){
    
    Base.x = x;
    Base.y = y;
    Base.w = width;
    Base.h = height;
}

bool UI::addComponent(int x, int y, int w, int h){
    //first check to see if its a valid component
    if(x < 0 || y < 0 || (y + h) > (Base.y + Base.h) || (x + w) > (Base.x + Base.w) ){
        return false;
    }
    else{
        SDL_Rect temp = {x+Base.x,y+Base.y, w, h};
        Component comp = {temp, 0 ,0};
        components.push_back(comp);
        return true;
    }
}

SDL_Point UI::getCenterOfUI(){
    SDL_Point temp = {Base.x+(Base.w/2), Base.y+(Base.h/2)};
    return temp;
}
