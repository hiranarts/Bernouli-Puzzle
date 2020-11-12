//
//  main.cpp
//  hamburger
//
//  Created by Ali Hamdani on 11/2/20.
//

#include <iostream>
#include "Core.hpp"
#include "Controller.hpp"
#include "Board.hpp"
#include "UI.hpp"
#include "Texture.hpp"

void initGameUI(UI* menu){
    SDL_Point center = menu->getCenterOfUI();
    int width = 40;
    int height = 30;
    //menu->addComponent(center.x-(width/2), center.y-(height/2), width, height);
    menu->createSlider(width, height, 100);
    
}

void initBoardUI(UI* board){
    SDL_Point center = board->getCenterOfUI();
    //TODO: I want to make it so that its adding each tile as its own component
    int tile_size = 60;
    int width = tile_size * 6;
    int height = tile_size * 6;
    for (int i = 0; i < 6; i++){
        for (int j = 0; j <6; j++ ){
            board->addComponent((center.x - width/2 + j*tile_size), (center.y - height/2 + i*tile_size), 50, 50);
        }
    }
    //board->addComponent(center.x - width/2, center.y - height/2, width , height);
}

void drawUI( SDL_Renderer* RENDERER,UI* ui){
    for(int i = 0 ; i < ui->components.size(); i++){
        if(ui->components[i].clicked > 0){
            SDL_SetRenderDrawColor(RENDERER, 104, 4, 21, SDL_ALPHA_OPAQUE);
        }
        else{
            SDL_SetRenderDrawColor(RENDERER, 12, 4, 102, SDL_ALPHA_OPAQUE);
        }
        SDL_RenderFillRect(RENDERER, &ui->components[i].area);
    }
}

void drawAspectRatioGrid(int xaspect, int yaspect,Core* DEVICE){
    SDL_SetRenderDrawColor(DEVICE->RENDERER, 255, 255, 255, SDL_ALPHA_OPAQUE);
    //draw columns
    for (int i = 0; i < xaspect; i++){
        SDL_RenderDrawLine(DEVICE->RENDERER, i*(DEVICE->width/xaspect), 0, i*(DEVICE->width/xaspect), DEVICE->height);
    }
    //draw rows
    for (int j = 0; j < yaspect; j++){
        SDL_RenderDrawLine(DEVICE->RENDERER, 0, j*(DEVICE->height/yaspect), DEVICE->width, j*(DEVICE->height/yaspect));
    }
}

const int aspect_tile_size = 46;

int main(int argc, const char * argv[]) {
    // insert code here...
    Core Core;
    Controller controller;
    Board board;
    UI board_control(0,aspect_tile_size*10,(aspect_tile_size*9),(aspect_tile_size*6));
    UI board_grid(0,0,aspect_tile_size*9,aspect_tile_size*10);
    initGameUI(&board_control);
    initBoardUI(&board_grid);
    Texture text(0,0,60,60);
    text.setFont("fonts/CaviarDreams.ttf", 24);
    //SDL_Color white = {255,255,255};
    //char which_tile[100];
    while(!controller.quit){
        controller.pollEvents();
        
        //update board
        board_grid.mouseSelection(&controller);
        //update UI
        board_control.mouseSelection(&controller);
        //slidershit
        board_control.sliderPosition();
        //timah to dra
        SDL_SetRenderDrawColor(Core.RENDERER, 32, 98, 187, 12);
        SDL_RenderFillRect(Core.RENDERER, &board_control.Base);
        SDL_SetRenderDrawColor(Core.RENDERER, 254, 232, 87, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(Core.RENDERER, &board_control.slider.area);
        SDL_SetRenderDrawColor(Core.RENDERER, 0, 130, 23, 30);
        SDL_RenderFillRect(Core.RENDERER, &board_grid.Base);
        
        
        
        
        drawUI(Core.RENDERER, &board_grid);
        //draw 9:16 grid
        drawAspectRatioGrid(9,16,&Core);
        //text.render(Core.RENDERER);

        SDL_RenderPresent(Core.RENDERER);


        
    }
     
    return 0;
}
