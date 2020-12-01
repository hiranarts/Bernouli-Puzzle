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
#include <unordered_map>
#include <array>
#include "SDL.h"
#include "Controller.hpp"

using namespace std;

class Board {
    
public:
    //0 for normal , 1 for chain ,2 for set evidence
    int mode;
    Board();
    int size;
    vector<float> bernoulis;
    vector<float> bernoulis2;
    vector<float> vals;
    vector<bool> active;
    vector<int> parents;
    //0 for not happend 1 for happened 2 for unknown
    vector<int> value;
    //{up,down,left,right}
    vector< array<int,4> > children;
    //input selected id and it will return a chainID
    unordered_map<int, int> indexToChain;
    //input a chain id and index it will return the parent index
    vector< unordered_map<int, int> > chain;
    
    vector<SDL_Rect> pieces;
    
    //vector<int> joined;
    void activate(int i);
    void deactivate(int i);
    void printBoard();
    void updateBernouli(int i, float p,float val);
    void updateBernouli2(int i, float p, float val);
    void formatPieces(SDL_DisplayMode* Device, int normal_tile);
    void renderPieces(SDL_Renderer* r);
    
    void updateTotalProbability();
    //state of board
    float eventProb;
    int selected_piece;
    void selectPiece(Controller* controller);
    
    //chain sshit
    void startChain(int parent, int child);
    float getProbChain(int index);
    bool hasParents(int index);
    bool hasChildren(int index);
    
    
};

#endif /* Board_hpp */
