//
//  Slider.cpp
//  detectiveBayes
//
//  Created by Ali Hamdani on 11/24/20.
//

#include "Slider.hpp"

Slider::Slider(SDL_Rect b, int r){
    button = b;
    origin = b.x + b.w/2;
    range = b.x + b.w/2 + r;
    val = 0.0f;
    
}

void Slider::render(SDL_Renderer *r){
    SDL_SetRenderDrawColor(r, 0, 123, 34, 255);
    SDL_RenderFillRect(r, &button);
}

void Slider::update(Controller* inputs){
    if(inputs->touch > 0){
        if(SDL_PointInRect(&inputs->touchPosition, &button)){
            moveSlider(inputs->touchPosition.x);
        }
    }
    printf("Val %f\n", val);
}

void Slider::moveSlider(int x){
    //first do bound detection
    if(x < origin){
        button.x = origin - button.w/2;
    }
    else if(x > range){
        button.x = range - button.w/2;
    }
    else{
        button.x = x - button.w/2;
    }
    
    val = ((0.0f + button.x+button.w/2) - origin)/(range - origin);
    float var = (int)(val * 100 + .5);
    val = var/100;
}

void Slider::moveSliderToPosition(float x){
    
    //round input to 2 decimal places
    float var = (int)(x * 100 + .5);
    x = var/100;
    
    button.x = x*(range-origin) + origin - button.w/2;
    
    val = x;
}


