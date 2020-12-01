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
        array<int, 4> ch = {-1,-1,-1,-1};
        children.push_back(ch);
        value.push_back(2);
        bernoulis2.push_back(0.0f);
    }
    selected_piece = -1;
    size = 0;
    mode = 0;
    
}

void Board::updateBernouli2(int i, float p, float val){
    if (p >1 || p < 0){
        printf("INCORRECT INPUT FOR BERNOULI RV\n");
    }
    if(i > bernoulis2.size() || i < 0){
        //printf("INCORRECT INPUT FOR BERNOULI INDEX\n");
    }
    else{
        bernoulis2[i] = p;
        //printf("%d\n", i);
        vals[i] = val;
    }
}

void Board::selectPiece(Controller* controller){
    if(controller->touch > 0){
        if(mode == 0){
            for (int i = 0; i < pieces.size(); i++){
                if(SDL_PointInRect(&controller->touchPosition, &pieces[i])){
                    selected_piece = i;
                    break;
                }
            }
        }
        else if(mode == 1){
            int i = selected_piece;
            if(i-4 >= 0 && !active[i-4]){
                if(SDL_PointInRect(&controller->touchPosition, &pieces[i-4])){
                    selected_piece = i-4;
                    //if already in a chain we want to add to the tree
                    //add piece to chain
                    parents[selected_piece] = i;
                    children[i][0] = selected_piece;
                    active[i] = true;
                    active[selected_piece] = true;
                    mode = 0;
                    printf("Index %d, Parent [%d], children [%d,%d,%d,%d]", selected_piece, parents[selected_piece] , children[i][0],children[i][1],children[i][2],children[i][3]);
                    
                }
            }
            if(i-1 >= 0 && (i-1)%4 != 3 && !active[i-1]){
                if(SDL_PointInRect(&controller->touchPosition, &pieces[i-1])){
                    selected_piece = i-1;
                    parents[selected_piece] = i;
                    children[i][2] = selected_piece;
                    active[i] = true;
                    active[selected_piece] = true;
                    mode = 0;
                    printf("Index %d, Parent [%d], children [%d,%d,%d,%d]", selected_piece, parents[selected_piece] , children[i][0],children[i][1],children[i][2],children[i][3]);

                }
            }
            if(i+1 <= bernoulis.size()-1 && (i+1)%4 != 0 && !active[i+1]){
                if(SDL_PointInRect(&controller->touchPosition, &pieces[i+1])){
                    selected_piece = i+1;
                    parents[selected_piece] = i;
                    children[i][3] = selected_piece;
                    active[i] = true;
                    active[selected_piece] = true;
                    mode = 0;
                    printf("Index %d, Parent [%d], children [%d,%d,%d,%d]", selected_piece, parents[selected_piece] , children[i][0],children[i][1],children[i][2],children[i][3]);

                }
            }
            if(i+4 <= bernoulis.size()-1 && !active[i+4]){
                if(SDL_PointInRect(&controller->touchPosition, &pieces[i+4])){
                    selected_piece = i+4;
                    parents[selected_piece] = i;
                    children[i][1] = selected_piece;
                    active[i] = true;
                    active[selected_piece] = true;
                    mode = 0;
                    printf("Index %d, Parent [%d], children [%d,%d,%d,%d]", selected_piece, parents[selected_piece] , children[i][0],children[i][1],children[i][2],children[i][3]);

                }
            }
        }
    }
}

void Board::renderPieces(SDL_Renderer* r){
    //if mode is normal
    if (mode == 0){
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
    //if player want to add a chain
    else if(mode == 1){
        int i = selected_piece;
        SDL_SetRenderDrawColor(r, 238,130,238, 255);
        if(i-4 >= 0 && !active[i-4]){SDL_RenderFillRect(r, &pieces[i-4]);}
        if(i-1 >= 0 && (i-1)%4 != 3 && !active[i-1]){SDL_RenderFillRect(r, &pieces[i-1]);}
        if(i+1 <= bernoulis.size()-1 && (i+1)%4 != 0 && !active[i+1]){SDL_RenderFillRect(r, &pieces[i+1]);}
        if(i+4 <= bernoulis.size()-1 && !active[i+4]){SDL_RenderFillRect(r, &pieces[i+4]);}
        SDL_RenderFillRect(r, &pieces[i]);
        
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

float Board::getProbChain(int index){
    //find prob chain
    float evidence = 1;
    float parent_prob = bernoulis[index];
    
    for (int i = 0; i < 4; i++){
        int childID = children[index][i];
        if(childID != -1 || value[childID] != 2){
            //probability given parent happened
            float mode1_prob = bernoulis[childID];
            //probability given parent did not happen
            float mode0_prob = bernoulis2[childID];
            
            
            if(value[childID] == 0){
                //P(~ID) = P(~ID|Parent = 1)*P(Parent) + P(~ID|Parent = 0)P(~Parent).
                float P_cid = (1-mode1_prob)*parent_prob + (1-mode0_prob)*(1-parent_prob);
                //P(Parent|~ID) = P(~ID|Parent)P(Parent)/P(~ID)
                parent_prob = parent_prob * (1-mode1_prob);
                evidence = evidence * P_cid;
            }
            else if(value[childID] == 1){
                //P(ID) = P(ID|Parent = 1)*P(Parent) + P(ID|Parent = 0)P(~Parent).
                float P_cid = (mode1_prob)*parent_prob + (mode0_prob)*(1-parent_prob);
                //P(Parent|ID) = P(ID|Parent)P(Parent)/P(ID)
                parent_prob = parent_prob * (mode1_prob);
                evidence = evidence * P_cid;
            }
        }
    }
    //P(Parent|evidence) = P(evidence|Parent)P(Parent)/P(evidence)
    return parent_prob/evidence;
    
}

bool Board::hasParents(int index){
    if (parents[index] != -1){
        return true;
    }
    return false;
}

bool Board::hasChildren(int index){
    for (int i = 0; i < 4; i++){
        if (children[index][i] != -1){
            return true;
        }
    }
    return false;
}
