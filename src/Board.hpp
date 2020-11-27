//
//  Board.hpp
//  hamburger
//
//  Created by Ali Hamdani on 11/4/20.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include <vector>
#include "SDL.h"
#include "Controller.hpp"

using namespace std;

class Board {
    
public:
    
    Board();
    int size;
    vector<float> bernoulis;
    vector<float> vals;
    vector<bool> active;
    vector<int> parents;
    vector<SDL_Rect> pieces;
    
    //vector<int> joined;
    void activate(int i);
    void deactivate(int i);
    void printBoard();
    void updateBernouli(int i, float p,float val);    
    void formatPieces(SDL_DisplayMode* Device, int normal_tile);
    void renderPieces(SDL_Renderer* r);
    
    void updateTotalProbability();
    //state of board
    float eventProb;
    int selected_piece;
    void selectPiece(Controller* controller);
    
    
};

#endif /* Board_hpp */
