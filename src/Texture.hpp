//
//  Texture.hpp
//  detectiveBayes
//
//  Created by Ali Hamdani on 11/26/20.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include "SDL.h"
#include "SDL_ttf.h"

class Texture{
public:
    SDL_Rect location;
    SDL_Texture *c_texture;
    Texture();
    ~Texture();
    
    void free();
    
    void updateLocation(int x , int y);
    void createTextureFromString(SDL_Renderer *r,TTF_Font *font, char str[]);
    void render(SDL_Renderer *r);
    
    void renderRect(SDL_Renderer *r, SDL_Color color);
};

#endif /* Texture_hpp */
