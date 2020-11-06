//
//  UI.hpp
//  hamburger
//
//  Created by Ali Hamdani on 11/5/20.
//

#ifndef UI_hpp
#define UI_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

typedef struct Component{
    SDL_Rect area;
    int hover;
    int clicked;
    
}Component;
//UI is whenever i want to have a menu or inventory screen
class UI{
private:
    //base area, everything should be located relative to this rectangle
    
    
public:
    SDL_Rect Base;

    vector<Component> components;
    
    UI(int x , int y, int width, int height);
    //x and y are relative to the base of the UI
    bool addComponent(int x, int y, int w, int h);
    //format components vector based on type of organization, ie centered list, left scroll,custom
    //TODO: First implement centered list
    void formatComponents();
    //get center position
    SDL_Point getCenterOfUI();
    SDL_Point getCenterOfComponent(int i, int j);
    
};

#endif /* UI_hpp */
