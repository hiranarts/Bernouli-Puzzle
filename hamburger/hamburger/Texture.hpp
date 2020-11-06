//
//  TextureLoader.hpp
//  hamburger
//
//  Created by Ali Hamdani on 11/5/20.
//

#ifndef TextureLoader_hpp
#define TextureLoader_hpp

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
class Texture{
public:
    //Initializes variables
    Texture(int x, int y, int w, int h);
    //Deallocates memory
    ~Texture();
    void free();
    //create texture from text that fits the texture box.
    void textureFromString(std::string input, SDL_Color color,SDL_Renderer* Render);
    void setFont(std::string path,int size);
    
    void render(SDL_Renderer* Render);
private:
    SDL_Texture* mTexture;
    TTF_Font* font;
    
    //Image dimensions
    SDL_Rect dimensions;
    
};
#endif /* TextureLoader_hpp */
