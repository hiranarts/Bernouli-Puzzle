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
    int width = 150;
    int height = 30;
    menu->addComponent(center.x-(width/2), center.y-(height/2), width, height);
}



int main(int argc, const char * argv[]) {
    // insert code here...
    Core Core;
    Controller controller;
    Board board;
    UI menu(0 ,0,Core.width,Core.height);
    initGameUI(&menu);

    int square_length = Core.width/9;
    Texture text(0,0,60,60);
    text.setFont("fonts/CaviarDreams.ttf", 46);
    SDL_Color white = {255,255,255};
    text.textureFromString("Hello Warudo", white, Core.RENDERER);

    

    while(!controller.quit){
        controller.pollEvents();
        if(controller.mLeftClick>0){
            menu.addComponent(controller.mPosition.x, controller.mPosition.y, 30, 30);
        }
        //timah to dra
        SDL_SetRenderDrawColor(Core.RENDERER, 32, 98, 187, 12);
        SDL_RenderFillRect(Core.RENDERER, &menu.Base);
        SDL_SetRenderDrawColor(Core.RENDERER, 254, 232, 87, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(Core.RENDERER, &menu.components[0].area);
        //draw 9:16 grid
        //draw cols
        SDL_SetRenderDrawColor(Core.RENDERER, 255, 255, 255, SDL_ALPHA_OPAQUE);
        for (int i = 0; i < 9; i++){
            SDL_RenderDrawLine(Core.RENDERER, i*square_length, 0, i*square_length, Core.height);
        }
        //draw rows
        for (int j = 0; j < 16; j++){
            SDL_RenderDrawLine(Core.RENDERER, 0, j*square_length, Core.width, j*square_length);
        }
        text.render(Core.RENDERER);
        
        SDL_RenderPresent(Core.RENDERER);


        
    }
     
    return 0;
}
