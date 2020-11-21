//
//  Controller.cpp
//  hamburger
//
//  Created by Ali Hamdani on 11/3/20.
//

#include "Controller.hpp"

Controller::Controller(){
    up = 0;
    down = 0;
    left = 0;
    right = 0;
    
    quit = false;
    
    click = 0;
    touch = 0;
    
    SDL_GetMouseState(&mPosition.x, &mPosition.y);
}

void Controller::pollEvents(SDL_DisplayMode* gMode){
    //TODO:Find a more elegant solution for mouse/touch holds
    //mouse holds
    if(click>0){
        click+=1;
    }
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        up += 1;
                        break;
                    case SDLK_DOWN:
                        down += 1;
                        break;
                    case SDLK_LEFT:
                        left += 1;
                        break;
                    case SDLK_RIGHT:
                        right += 1;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        up = 0;
                        break;
                    case SDLK_DOWN:
                        down = 0;
                        break;
                    case SDLK_LEFT:
                        left = 0;
                        break;
                    case SDLK_RIGHT:
                        right = 0;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&mPosition.x, &mPosition.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                click = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                click = 0;
                break;
            case SDL_FINGERDOWN:
                touchPosition.x = event.tfinger.x * gMode->w;
                touchPosition.y = event.tfinger.y * gMode->h;
                touch += 1;
                break;
            case SDL_FINGERMOTION:
                touchPosition.x = event.tfinger.x * gMode->w;
                touchPosition.y = event.tfinger.y * gMode->h;
            case SDL_FINGERUP:
                touchPosition.x = event.tfinger.x * gMode->w;
                touchPosition.y = event.tfinger.y * gMode->h;
                touch = 0;
            default:
                break;
        }
    }
}

void Controller::printControl(){
    printf("mouse %d , %d \n" , mPosition.x , mPosition.y);
    printf("up frames %d \n" , up);
    printf("left lick %d \n" , click);
}
