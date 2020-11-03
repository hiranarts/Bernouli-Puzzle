//
//  Core.cpp
//  hamburger
//
//  Created by Ali Hamdani on 11/2/20.
//

#include "Core.hpp"

bool Core::init(){
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        SDL_Log("SDL could not be initialized! SDL ERROR: %s\n", SDL_GetError());
        return false;
    }
    if (!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG)){
        SDL_Log("SDL_image could not be initialized! IMG ERROR: %s\n",IMG_GetError());
        return false;
    }
    if (TTF_Init() < 0){
        SDL_Log("SDL_ttf could not be initialized! TTF ERROR: %s\n", TTF_GetError());
        return false;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0) {
        SDL_Log("SDL_mixer could not be initialized! MIX ERROR: %s\n", SDL_GetError());
        return false;
    }
    else{
        return true;
    }
}

bool Core::initWindowAndRenderer(){
    //find device attributes
    if(SDL_GetCurrentDisplayMode(0, &DEVICE) != 0){
        SDL_Log("Could not capture current display mode! ERROR: %s\n", SDL_GetError());
        return false;
    }
    GAME_WINDOW = SDL_CreateWindow("HAMBURGER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 414, 736, SDL_WINDOW_OPENGL);
    if(GAME_WINDOW == NULL){
        SDL_Log("GAME_WINDOW could not be created! ERROR %s\n", SDL_GetError());
        return false;
    }
    else{
        RENDERER = SDL_CreateRenderer(GAME_WINDOW, -1, SDL_RENDERER_ACCELERATED);
        if(RENDERER == NULL){
            SDL_Log("RENDERER could not be created! ERROR %s\n", SDL_GetError());
            return false;
        }
        else{
            return true;
        }
    }
}
Core::Core(){
    if (!init()){
        SDL_Log("SDL framkeworks are not working please fix me!\n");
    }
    else{
        //start initializing windows renderers
        if(!initWindowAndRenderer()){
            SDL_Log("Window and Renderer are not able to be created please fix me!\n");
        }
    }
}
