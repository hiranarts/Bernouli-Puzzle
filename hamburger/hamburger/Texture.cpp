//
//  TextureLoader.cpp
//  hamburger
//
//  Created by Ali Hamdani on 11/5/20.
//

//texture load

#include "Texture.hpp"


Texture::Texture(int x, int y, int w, int h){
    dimensions.x = x;
    dimensions.y = y;
    dimensions.w = w;
    dimensions.h = h;
    
    mTexture = NULL;
    
}
void Texture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        
        dimensions.w = 0;
        dimensions.h = 0;
    }
}

Texture::~Texture()
{
    //Deallocate
    free();
}

void Texture::setFont(std::string path,int size){
    //free font
    printf("How many?\n");
    TTF_CloseFont(font);
    font = NULL;
    
    font = TTF_OpenFont(path.c_str(), size);
    
    if (font == NULL){
        printf("New font could not set\n");
    }

}



void Texture::textureFromString(SDL_Renderer* Render,SDL_Color color,std::string input,TTF_Font* gFont){
    //this frees the mTexture not the font
    free();
    SDL_Surface* temp = TTF_RenderText_Blended(gFont, input.c_str(), color);
    if (temp == NULL){
        printf("Text surface could not be rendered!\n");
    }
    else{
        mTexture = SDL_CreateTextureFromSurface(Render, temp);
        if(mTexture == NULL){
            printf("Text texture could not be initialized\n");
        }
        else{
            SDL_QueryTexture(mTexture, NULL, NULL, &dimensions.w, &dimensions.h);
        }
        SDL_FreeSurface(temp);
    }
    
}

void Texture::render(SDL_Renderer* Render){
    SDL_RenderCopy(Render, mTexture, NULL, &dimensions);
}
