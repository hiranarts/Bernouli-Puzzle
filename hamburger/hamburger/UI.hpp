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
#include "Controller.hpp"
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
    //slider that is a one off
    //how far can the slider move from its center
    //TODO: This should be calculated from a single value
    int slider_max_range;
    int slider_min_range;
    
public:
    SDL_Rect Base;
    float slider_position;
    vector<Component> components;
    //figure out which component was clicked on
    void mouseSelection(Controller* controller);
    UI(int x , int y, int width, int height);
    //x and y are relative to the base of the UI
    bool addComponent(int x, int y, int w, int h);
    //format components vector based on type of organization, ie centered list, left scroll,custom
    //TODO: First implement centered list
    void formatComponents();
    //get center position
    SDL_Point getCenterOfUI();
    SDL_Point getCenterOfComponent(int i, int j);
    Component slider;
    void createSlider(int width, int height, int range);
    void updateSlider(SDL_Point mousePosition);
    void sliderPosition();
    
    
};

#endif /* UI_hpp */
