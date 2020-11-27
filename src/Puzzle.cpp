//
//  Puzzle.cpp
//  detectiveBayes
//
//  Created by Ali Hamdani on 11/22/20.
//

#include "Puzzle.hpp"

Puzzle::Puzzle(){
    //first initiialize the board grid
    no_pieces = 16;
    
    board = new Board();
    
    
    
}

void Puzzle::initFont(int normalizer){
    //TODO: need to replace this with normalizer
    controlFont = TTF_OpenFont("assets/Bebas-Regular.ttf", normalizer);
    if(controlFont == NULL){
        printf("\n control font was not initialized \n");
    }
}



void Puzzle::initSliders(){
    
}

//we know first 9 pieces are of the board
void Puzzle::init(SDL_DisplayMode* Device, int normal_tile){
    
    board->formatPieces(Device, normal_tile);
    
    SDL_Rect b = {normal_tile*5,normal_tile*13,normal_tile*1,normal_tile*1};
        
    int range = normal_tile*3;
    
    sliders[0] = new Slider(b,range);
    
    prob_text.location.x = normal_tile*1;
    prob_text.location.y = normal_tile*13;
    
    prob_dependent_text.location.x = normal_tile*1;
    prob_dependent_text.location.y = normal_tile*12;
        
    prob_chain_text.location.x = normal_tile*1;
    prob_chain_text.location.y = normal_tile*11;
    
    prob_total_text.location.x = normal_tile*1;
    prob_total_text.location.y = normal_tile*10;

    //initialize buttons
    Texture temp;
    buttons.push_back(temp);
    buttons[0].location.x = normal_tile*1;
    buttons[0].location.y = normal_tile*15;
    buttons[0].location.w = normal_tile;
    buttons[0].location.h = normal_tile;
    
    Texture newtemp;
    buttons.push_back(newtemp);
    buttons[1].location.x = normal_tile*3;
    buttons[1].location.y = normal_tile*15;
    buttons[1].location.w = normal_tile;
    buttons[1].location.h = normal_tile;
    
    
}

void Puzzle::inputButtons(Controller *inputs){
    int selected = -1;
    if(inputs->touch > 0){
        for(int i = 0; i < buttons.size(); i++){
            if(SDL_PointInRect(&inputs->touchPosition, &buttons[i].location)){
                //some chance
                selected = i;
                break;
            }
        }
    }
    //we know that selected piece is greater than 0
    if(selected > -1){
        switch (selected) {
            //activate button
            case 0:
                board->activate(board->selected_piece);
                break;
            //deactivate button
            case 1:
                board->deactivate(board->selected_piece);
                break;
            default:
                break;
        }
    }
}

void Puzzle::gameLoop(Controller* inputs){
    //update state of board
    board->selectPiece(inputs);
    //look for inputs in slider
    if(board->selected_piece > -1){
        sliders[0]->moveSliderToPosition(board->bernoulis[board->selected_piece]);
        sliders[0]->update(inputs);
        board->updateBernouli(board->selected_piece, sliders[0]->val, 1);
        //look for inputs in buttons
        inputButtons(inputs);
    }
    
    board->updateTotalProbability();
    
}

void Puzzle::updateText(SDL_Renderer* r){
    
    //TODO: change once board functions get fixed
    prob_dependent_text.createTextureFromString(r, controlFont, "P(X|1) ~ ");
    prob_chain_text.createTextureFromString(r, controlFont, "P(CHAIN) ~ ");

    //total grid probability
    char total[50];
    prob_total_text.free();
    snprintf(total, 50, "P(TOTAL) ~ %.2f", board->eventProb);
    prob_total_text.createTextureFromString(r, controlFont, total);
    
    if(board->selected_piece>=0){
        prob_text.free();
        char label[50];
        snprintf(label, 50, "P(X)~%.2f",board->bernoulis[board->selected_piece]);
        prob_text.createTextureFromString(r, controlFont, label);
    }
    
}



void Puzzle::render(SDL_Renderer* r){
    board->renderPieces(r);
    sliders[0]->render(r);
    prob_text.render(r);
    prob_dependent_text.render(r);
    prob_chain_text.render(r);
    prob_total_text.render(r);
    
    SDL_Color green = {13,198,56,255};
    buttons[0].renderRect(r, green);
    SDL_Color red = {243, 32,43,255};
    buttons[1].renderRect(r, red);
    
    
}




