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
        active.push_back(false);
        clicked.push_back(0);
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

void Board::updateBernouli2(int i, float p){
    if (p >1 || p < 0){
        printf("INCORRECT INPUT FOR BERNOULI RV\n");
    }
    if(i > bernoulis2.size() || i < 0){
        //printf("INCORRECT INPUT FOR BERNOULI INDEX\n");
    }
    else{
        bernoulis2[i] = p;
        //printf("%d\n", i);
    }
}

void Board::selectPiece(Controller* controller){
    //user held down piece and the user is still touching
    if (chain_mode && controller->touch == 0){
        printf("undue chain mode\n");
        chain_mode = false;
    }
    if (mode == 2 and controller->touch > 0){
        for(int i = 0; i < pieces.size(); i++){
            if(hasParents(i)){
                if(SDL_PointInRect(&controller->touchPosition, &pieces[i])){
                    setEvidence(i);
                }
            }
        }
    }
    if(chain_mode && controller->touch > 0){
        int i = selected_piece;
        if(i-4 >= 0 && !active[i-4]){
            //up
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
                chain_mode = false;
                controller->touch = 0;
                size++;
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
                chain_mode = false;
                controller->touch = 0;
                size++;

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
                chain_mode = false;
                controller->touch = 0;
                size++;


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
                chain_mode = false;
                controller->touch = 0;
                size++;

            }
        }
    }
    if(controller->touch > 0){
        if(mode == 0){
            for (int i = 0; i < pieces.size(); i++){
                if(SDL_PointInRect(&controller->touchPosition, &pieces[i])){
                    selected_piece = i;
                    clicked[i] += 1;
                    if(clicked[i] > 30 && active[i] && !hasParents(i)){
                        printf("chain mode activate%d\n",i);
                        chain_mode = true;
                    }
                    break;
                }
                else
                {
                    clicked[i] = 0;
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
    if(chain_mode){
        int i = selected_piece;
        SDL_SetRenderDrawColor(r, 238,130,238, 255);
        if(i-4 >= 0 && !active[i-4]){SDL_RenderFillRect(r, &pieces[i-4]);}
        if(i-1 >= 0 && (i-1)%4 != 3 && !active[i-1]){SDL_RenderFillRect(r, &pieces[i-1]);}
        if(i+1 <= bernoulis.size()-1 && (i+1)%4 != 0 && !active[i+1]){SDL_RenderFillRect(r, &pieces[i+1]);}
        if(i+4 <= bernoulis.size()-1 && !active[i+4]){SDL_RenderFillRect(r, &pieces[i+4]);}
        SDL_RenderFillRect(r, &pieces[i]);
        
    }
    //set evidence mode
    if(mode == 2){
        for (int i = 0; i < pieces.size(); i++){
            SDL_SetRenderDrawColor(r,235,50*value[i],100,255);
            if(hasParents(i)){
                SDL_RenderFillRect(r, &pieces[i]);
            }
        }
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
        if(hasParents(i)){
            printf("has parents and I am tring to delete it");
            int p = parents[i];
            for(int c = 0; c < 4; c++){
                if(children[p][c] == i){
                    printf("deleted child from parent %d", i);
                    children[p][c] = -1;
                    parents[i] = -1;
                    break;
                }
            }
        }
        if(hasChildren(i)){
            for(int c = 0; c < 4; c++){
                if(children[i][c] != -1){
                    printf("child about to be deleted: %d\n", children[i][c]);
                    deactivate(children[i][c]);
                }
            }
        }
        active[i] = false;
        bernoulis[i] = 0;
        bernoulis2[i] = 0;
        value[i] = 2;
        size--;
    }
}
void Board::activate(int i){
    if(active[i] != true){
        active[i] = true;
        size++;
    }
    
}

void Board::updateBernouli(int i, float p){
    if (p >1 || p < 0){
        printf("INCORRECT INPUT FOR BERNOULI RV\n");
    }
    if(i > bernoulis.size() || i < 0){
        //printf("INCORRECT INPUT FOR BERNOULI INDEX\n");
    }
    else{
        bernoulis[i] = p;
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
        if(active[i] == true && !hasParents(i)){
            if(hasChildren(i)){
                total_prob = total_prob * getProbChain(i);
            }
            else{
                total_prob = total_prob * bernoulis[i];
            }
        }
    }
    eventProb = total_prob;
}

float Board::getProbChain(int index){
    //find prob chain
    float evidence = 1.0f;
    float parent_prob = bernoulis[index];
    float numerator = 1.0f;


    
    for (int i = 0; i < 4; i++){
        if(children[index][i] != -1){
            int childID = children[index][i];
            if(value[childID] != 2){
                //probability given parent happened
                float mode1 = bernoulis[childID];
               
                //probability given parent did not happen
                float mode0 = bernoulis2[childID];
                
                //P(~ID) = P(~ID|Parent = 1)*P(Parent) + P(~ID|Parent = 0)P(~Parent).
                float P_ID = mode1*parent_prob + mode0*(1-parent_prob);
                
                
                if(value[childID] == 0){
                    //p(X) = product [P(ID)]
                    evidence *= (1-P_ID);
                    numerator *= 1-mode1;
                }
                if(value[childID] == 1){
                    evidence *= P_ID;
                    numerator *= mode1;
                }
            }
        }
    }
    //P(Parent|evidence) = P(evidence|Parent)P(Parent)/P(evidence)
    return (parent_prob*numerator)/evidence;
    
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

void Board::setEvidence(int index){
    value[index] = (value[index] + 1)%3;
}


bool Board::submit(vector<float> answer,vector<float> answer2,vector<int> evid){
    //size check
    if(answer.size() != size){
        if(answer.size() < size){
            printf("Too many tiles\n");
            return false;
        }
        else{
            printf("Too few tiles\n");
            return false;
        }
    }
    vector<int> checked;
    for(int i = 0; i < answer.size(); i++){
        for(int j = 0; j < bernoulis.size(); j++){
            if(answer[i] == bernoulis[j] && answer2[i] == bernoulis2[j] && evid[i] == value[j] && (count(checked.begin(), checked.end(), j) == 0)){
                printf("id:%d answer:%.2f ,answer2:%.2f evidence:%d\n",j,bernoulis[j] , bernoulis2[j],value[j]);
                checked.push_back(j);
                break;
            }
        }
    }
    if(checked.size() != answer.size()){
        printf("No bueno\n");
        return false;
    }
    printf("bueno\n");
    return true;
}
