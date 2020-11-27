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
#include "Controller.hpp"
//SDL_Renderer* gRenderer;
using namespace std;
class Menu{
public:
    TTF_Font* menu_font;
    TTF_Font* title_font;
    
    Texture game_title_text;
    Texture level_title_text;
    
    vector<SDL_Rect> levels;
    int selectedLevel(Controller* inputs);
    
    SDL_Rect* credits_text;
    
    Menu(SDL_Renderer* r, SDL_DisplayMode* gMode, int normalizer,int no_levels);
    
    void formatButtons();
    
    //handle rendering and selection
    void menuLoop(SDL_Renderer* r,Controller* inputs);
    
    void render(SDL_Renderer *r);
    
};
#endif /* Menu_hpp */
