//
//  Puzzle.hpp
//  detectiveBayes
//
//  Created by Ali Hamdani on 11/22/20.
//

#ifndef Puzzle_hpp
#define Puzzle_hpp

#include <stdio.h>
#include "Texture.hpp"
#include "SDL.h"
#include "Board.hpp"
#include "Controller.hpp"
#include "Slider.hpp"
#include <string>
#include <vector>

class Puzzle{
public:
    //everything is public wtf

    
    Puzzle();

    int no_pieces;
    
    Board* board;
    
    Slider* sliders[2];
    
    Texture prob_text;
    
    Texture prob_dependent_text;
    
    Texture prob_chain_text;
    
    Texture prob_total_text;
    
        
    TTF_Font* controlFont;
    
    //buttons
    vector<Texture> buttons;
    
    
    void init(SDL_DisplayMode* Device, int normal_tile);
    
    void initSliders();
    
    void gameLoop(Controller* inputs);
    
    void render(SDL_Renderer* r);
    
    void initFont(int normalizer);
    
    void updateText(SDL_Renderer* r);
    
    void inputButtons(Controller *inputs);
};
#endif /* Puzzle_hpp */
