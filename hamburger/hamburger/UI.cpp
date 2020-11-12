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

void UI::createSlider(int width, int height, int range){
    
    SDL_Point center = getCenterOfUI();
    SDL_Rect temp = {center.x, center.y, width, height};
    slider.area = temp;
    slider.clicked = 0;
    slider.hover = 0;
    slider_position = 0.0f;
    
    slider_max_range = slider.area.x + range;
    slider_min_range = slider.area.x;
    
}

//slider location is going to be used for other functions
void UI::sliderPosition(){
    printf("slider pos %d\n", ((slider.area.x+slider.area.w/2) - slider_min_range));
}
void UI::updateSlider(SDL_Point mPosition){
    //first do bound detection
    if(mPosition.x < slider_min_range){
        slider.area.x = slider_min_range - slider.area.w/2;
    }
    else if(mPosition.x > slider_max_range){
        slider.area.x = slider_max_range - slider.area.w/2;
    }
    else{
        slider.area.x = mPosition.x - slider.area.w/2;
    }
}
void UI::mouseSelection(Controller* controller){
    //only do stuff if the mouse is clicked
    
    if(controller->mLeftClick>0){
        //update each components state based on mouse click position.
        
        for (int i = 0; i < components.size();i++){
            if(SDL_PointInRect(&controller->mPosition, &components[i].area)){
                components[i].clicked++;
            }
            else{
                //reset it to 0
                components[i].clicked = 0;
            }
            
        }
        if(SDL_PointInRect(&controller->mPosition, &slider.area)){
            slider.clicked++;
        }
    }
    //if the user released the mouse button
    else{
        //reset it to 0
        for(int i = 0; i < components.size(); i++){
            components[i].clicked = 0;
        }
        slider.clicked = 0;
    
    }
    
    if (slider.clicked > 0){
        updateSlider(controller->mPosition);
    }
}

//
bool UI::addComponent(int x, int y, int w, int h){
    //first check to see if its a valid component
    if(x < 0 || y < 0 || (y + h) > (Base.y + Base.h) || (x + w) > (Base.x + Base.w) ){
        return false;
    }
    else{
        SDL_Rect temp = {x,y, w, h};
        Component comp = {temp, 0 ,0};
        components.push_back(comp);
        return true;
    }
}

SDL_Point UI::getCenterOfUI(){
    SDL_Point temp = {Base.x+(Base.w/2), Base.y+(Base.h/2)};
    return temp;
}
