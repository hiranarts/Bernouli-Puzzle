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
    map<float, float> random_variables[5][7];
    
public:
    Board();
    int size;
    Board(int no_pieces);
    vector<float> bernoulis;
    vector<float> vals;
    vector<bool> active;
    //vector<int> joined;
    void activate(int i);
    void deactivate(int i);
    void printBoard();
    void updateBernouli(int i, float p,float val);
    void printRandomVariable(int i , int j);
    bool addPMF(int i, int j, float X, float P);
    bool subtractPMF(int i, int j, float X, float P);
    
    
};

#endif /* Board_hpp */
