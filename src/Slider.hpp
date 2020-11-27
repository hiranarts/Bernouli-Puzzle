//
//  Slider.hpp
//  detectiveBayes
//
//  Created by Ali Hamdani on 11/24/20.
//

#ifndef Slider_hpp
#define Slider_hpp

#include <stdio.h>
#include "SDL.h"
#include "Controller.hpp"

class Slider{
public:
    
    int range;
    int origin;
    float val;
    
    SDL_Rect button;
    
    Slider(SDL_Rect b, int r);
    
    void render(SDL_Renderer* r);
    
    void update(Controller* controller);
    
    void moveSlider(int x);
    
    void moveSliderToPosition(float x);
    
};

#endif /* Slider_hpp */
