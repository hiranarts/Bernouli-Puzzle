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
#include <map>
using namespace std;

class Board {
private:
    vector<float> bernoulis;
    map<float, float> random_variables[5][7];
    
public:
    Board();
    Board(int no_pieces);
    void printBoard();
    void updateBernouli(int i, float p);
    void printRandomVariable(int i , int j);
    bool addPMF(int i, int j, float X, float P);
    bool subtractPMF(int i, int j, float X, float P);
    
};

#endif /* Board_hpp */
