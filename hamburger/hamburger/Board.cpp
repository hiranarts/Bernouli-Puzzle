//
//  Board.cpp
//  hamburger
//
//  Created by Ali Hamdani on 11/4/20.
//

#include "Board.hpp"

Board::Board(){
    //initialize each random variable to have a 0 pmf with probability one
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 7; j++){
            random_variables[i][j].insert(make_pair(0, 1));
        }
    }
}

void Board::printRandomVariable(int i , int j){
    printf("X:%d, P:%.2f", 0,random_variables[i][j].at(0));
}

void Board::printBoard(){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 7; j++){
            //cout << random_variables
            printRandomVariable(i, j);
        }
    }
}

bool Board::addRandomVariable(int i, int j, float X, float P){
    if(random_variables[i][j].size() > 9){
        printf("Cant add any more random variables, too many pmfs\n");
        return false;
    }
    else{
        //first find if there is any probability left to give
        float zeroP = random_variables[i][j].at(0);
        if (zeroP > P){
            printf("Cant add this variable probability sum will exceed 1\n");
            return false;
        }
        else{
            random_variables[i][j][0] = P - zeroP;
            random_variables[i][j][X] = P;
            return true;
        }
        
    }
}
