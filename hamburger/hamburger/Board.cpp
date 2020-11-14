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

Board::Board(int no_pieces){
    //initialize all the bernouli rv
    for (int i = 0; i < no_pieces; i++){
        bernoulis.push_back(0.0f);
        vals.push_back(0.0f);
        active.push_back(false);
    }
    size = 0;
    
}

void Board::deactivate(int i){
    if (active[i] != false){
        active[i] = false;
        size--;
    }
}
void Board::activate(int i){
    if(active[i] != true){
        active[i] = true;
        size++;
    }
    
}
void Board::printRandomVariable(int i , int j){
    printf("X:%d, P:%.2f", 0,random_variables[i][j].at(0));
}

void Board::updateBernouli(int i, float p,float val){
    if (p >1 || p < 0){
        printf("INCORRECT INPUT FOR BERNOULI RV\n");
    }
    if(i > bernoulis.size() || i < 0){
        //printf("INCORRECT INPUT FOR BERNOULI INDEX\n");
    }
    else{
        bernoulis[i] = p;
        //printf("%d\n", i);
        vals[i] = val;
    }
}


void Board::printBoard(){
    
    for (int i = 0;  i< bernoulis.size() ; i++){
        //cout << random_variables
        printf("X:%d, P:%.2f", i,bernoulis[i]);

    }
    printf("\n");
    
}

bool Board::addPMF(int i, int j, float X, float P){
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
