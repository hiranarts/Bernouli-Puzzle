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
    SDL_Color black ={0,0,0};
    game_title_text.Render = r;
    game_title_text.loadFontFromFile("assets/Bebas-Regular.ttf", normal_tile);
    game_title_text.loadFromRenderedText("Detective Bayes", black);

    game_title_text.location.x = (Device->w - game_title_text.location.w)/2;
    game_title_text.location.y = normal_tile;
    
    //center rect;
   
    
    
    

}
