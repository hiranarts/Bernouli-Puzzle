//
//  Board.cpp
//  hamburger
//
//  Created by Ali Hamdani on 11/4/20.
//

#include "Board.hpp"

Board::Board(){
    //initialize all the bernouli rv
    for (int i = 0; i < 16; i++){
        bernoulis.push_back(0.0f);
        vals.push_back(0.0f);
        active.push_back(false);
        SDL_Rect temp;
        pieces.push_back(temp);
        //if parent is -1 then that means there are no dependencies. 
        parents.push_back(-1);
    }
    size = 0;
    
}

void Board::selectPiece(Controller* controller){
    bool found = false;
    if(controller->touch > 0){
        for (int i = 0; i < pieces.size(); i++){
            if(SDL_PointInRect(&controller->touchPosition, &pieces[i])){
                selected_piece = i;
                found = true;
                break;
            }
        }
        /* //deselecting piece 
        if(found == false && controller->touch > 20){
            selected_piece = -1;
        }
         */
    }
}

void Board::renderPieces(SDL_Renderer* r){
    for (int i =0; i < pieces.size(); i++){
        if(active[i] == true){
            SDL_SetRenderDrawColor(r, 233, 78, 69, 255);
        }
        else{
            SDL_SetRenderDrawColor(r, 69, 233, 123, 255);
        }
        SDL_RenderFillRect(r, &pieces[i]);
    }
    if (!(selected_piece < 0)){
        SDL_SetRenderDrawColor(r, 255, 0 , 123, 255);
        SDL_RenderFillRect(r, &pieces[selected_piece]);
    }
}

void Board::formatPieces(SDL_DisplayMode* Device, int normal_tile){
    int rows = 4;
    int cols = 16/rows;
    int tilesize = 2 * normal_tile;
    int offset_x = ( Device->w - (tilesize*cols) )/2;
    int offset_y = 1;
    //this means the inner tile is half the size of the grid tile
    float tilesize_ratio = .75;
    
    int counter = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){

            SDL_Rect temp = {offset_x + (j*tilesize) + ((tilesize - tilesize*tilesize_ratio)/2), offset_y*normal_tile+(i*tilesize) + ((tilesize - tilesize*tilesize_ratio)/2),
                tilesize*tilesize_ratio,
                tilesize*tilesize_ratio};
                        
            pieces[counter] = temp;
            counter++;
        }
    }
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

void Board::updateTotalProbability(){
    float total_prob = 1;
    for(int i = 0; i < active.size(); i++){
        if(active[i] == true){
            total_prob = total_prob * bernoulis[i];
        }
    }
    eventProb = total_prob;
}


