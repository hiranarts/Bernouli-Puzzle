//
//  Texture.hpp
//  detectiveBayes
//
//  Created by Ali Hamdani on 11/21/20.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <stdio.h>
#include <string>


//Texture wrapper class
class Texture
{
public:
    SDL_Renderer* Render;
    //Initializes variables
    Texture();

    //Deallocates memory
    ~Texture();

    //Loads image at specified path
    bool loadFromFile( std::string path );
    
    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

    //set Font
    bool loadFontFromFile(std::string path, int size);
    
    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );
    
    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //move texture location
    void moveTexture(int x, int y);
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
    SDL_Rect location;


private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    //font
    TTF_Font* font;
    //Image dimensions
    int mWidth;
    int mHeight;
};


#endif /* Texture_hpp */
