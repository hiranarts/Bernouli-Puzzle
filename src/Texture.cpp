//
//  Texture.cpp
//  detectiveBayes
//
//  Created by Ali Hamdani on 11/26/20.
//

#include "Texture.hpp"

Texture::Texture(){
    c_texture = NULL;
}

void Texture::updateLocation(int x, int y){
    location.x = x;
    location.y = y;
}

Texture::~Texture(){
    free();
}

void Texture::free(){
    if (c_texture != NULL){
        SDL_DestroyTexture(c_texture);
        c_texture = NULL;
        location.w = NULL;
        location.h = NULL;
    }
}

void Texture::createTextureFromString(SDL_Renderer *r, TTF_Font *font, char *str){
    free();
    SDL_Color black = {0,0,0};
    SDL_Surface* temp = TTF_RenderText_Blended(font, str, black);
    if (temp == NULL){
        printf("Text surface could not be rendered!\n");
    }
    else{
        c_texture = SDL_CreateTextureFromSurface(r, temp);
        if(c_texture == NULL){
            printf("Text texture could not be initialized\n");
        }
        else{
            SDL_QueryTexture(c_texture, NULL, NULL, &location.w, &location.h);
        }
        SDL_FreeSurface(temp);
    }
}

void Texture::createTextureFromStringWrapped(SDL_Renderer *r, TTF_Font *font, char *str){
    free();
    SDL_Color black = {0,0,0};
    SDL_Surface* temp = TTF_RenderText_Blended_Wrapped(font, str, black, location.w);
    if (temp == NULL){
        printf("Text surface could not be rendered!\n");
    }
    else{
        c_texture = SDL_CreateTextureFromSurface(r, temp);
        if(c_texture == NULL){
            printf("Text texture could not be initialized\n");
        }
        else{
            SDL_QueryTexture(c_texture, NULL, NULL, &location.w, &location.h);
        }
        SDL_FreeSurface(temp);
    }
}
void Texture::render(SDL_Renderer *r){
    SDL_RenderCopy(r, c_texture, NULL, &location);
}

void Texture::renderRect(SDL_Renderer *r, SDL_Color color){

    SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(r, &location);
    
}
