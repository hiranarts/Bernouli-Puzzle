//
//  Menu.cpp
//  detectiveBayes
//
//  Created by Ali Hamdani on 11/20/20.
//

#include "Menu.hpp"

Menu::Menu(SDL_Renderer* r, SDL_DisplayMode* Device, int normal_tile, int no_levels){
    int rows = 3;
    int cols = 15/rows;
    int tilesize = 1.5 * normal_tile;
    int offset_x = ( Device->w - (tilesize*cols) )/2;
    int offset_y = 5;
    //this means the inner tile is half the size of the grid tile
    float tilesize_ratio = .75;
    
    //tilesize determins offset
    //determine offset
    //3 by 5
    
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < 5; j++){
            SDL_Rect temp = {offset_x + (j*tilesize) + ((tilesize - tilesize*tilesize_ratio)/2), offset_y*normal_tile+(i*tilesize) + ((tilesize - tilesize*tilesize_ratio)/2),
                tilesize*tilesize_ratio,
                tilesize*tilesize_ratio};
            //printf("\n(%d,%d),%d:%d\n", temp.x, temp.y, temp.w, temp.h);
            levels.push_back(temp);

        }
    }
    
    //create Title text texture
    //TODO: FIXME WITH UPDATED TEXTURE CLASS
    
    TTF_Font *title_font = TTF_OpenFont("assets/Bebas-Regular.ttf", 1.5*normal_tile);
    game_title_text.createTextureFromString(r, title_font, "Bernouli Puzzle");
    
    //center rect;
    game_title_text.location.x = (Device->w - game_title_text.location.w)/2;
    game_title_text.location.y = normal_tile;
    
    //create levels title
    TTF_Font *subtitle_font = TTF_OpenFont("assets/Bebas-Regular.ttf", normal_tile);
    level_title_text.createTextureFromString(r, subtitle_font, "LEVELS");
     
    //center text
    level_title_text.location.x = (Device->w - level_title_text.location.w)/2;
    level_title_text.location.y = 4*normal_tile;
    
    
    //start menu loop
    
}

int Menu::selectedLevel(Controller* inputs){
    //if the users hand is on the screen
    if (inputs->touch > 0){
        for(int i = 0; i < levels.size(); i++){
            if(SDL_PointInRect(&inputs->touchPosition,&levels[i])){
                return i;
            }
        }
    }
    //return -1 if the user didnt select anything.
    return -1;
}

void Menu::menuLoop(SDL_Renderer* r, Controller *inputs){
    int selected = selectedLevel(inputs);
    SDL_SetRenderDrawColor(gRenderer, 123, 32, 122, 255);
    for (int i = 0; i < levels.size(); i++){
        SDL_RenderFillRect(r, &levels[i]);
    }
    //no level was selected
    if(!(selected<0)){
        SDL_SetRenderDrawColor(r, 3, 233, 123, 255);
        SDL_RenderFillRect(r, &levels[selected]);
    }
}

void Menu::render(SDL_Renderer *r){
    
}
