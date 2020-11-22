//
//  Menu.hpp
//  detectiveBayes
//
//  Created by Ali Hamdani on 11/20/20.
//

#ifndef Menu_hpp
#define Menu_hpp

#include <stdio.h>
#include <vector>
#include "SDL.h"
#include "Core.hpp"
#include "Texture.hpp"

//SDL_Renderer* gRenderer;
using namespace std;
class Menu{
public:
    TTF_Font* menu_font;
    TTF_Font* title_font;
    SDL_Rect game_title;
    Texture game_title_text;
    SDL_Rect level_title;
    Texture level_title_text;
    vector<SDL_Rect> levels;
    SDL_Rect credits;
    SDL_Rect* credits_text;
    Menu(SDL_Renderer* r, SDL_DisplayMode* gMode, int normalizer,int no_levels);
    void formatButtons();
};
#endif /* Menu_hpp */
