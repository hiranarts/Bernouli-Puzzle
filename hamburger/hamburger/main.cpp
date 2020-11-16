//
//  main.cpp
//  hamburger
//
//  Created by Ali Hamdani on 11/2/20.
//

#include <string>
#include <sstream>
#include <iostream>

#include "Core.hpp"
#include "Controller.hpp"
#include "Board.hpp"
#include "UI.hpp"
#include "Texture.hpp"
#include "SDL2_ttf/SDL_ttf.h"

const double FRAME_RATE = 60.0;
const double FRAME_DELAY = 1000/FRAME_RATE;

void initGameUI(UI* menu){
    
    int width = 40;
    int height = 30;
    //menu->addComponent(center.x-(width/2), center.y-(height/2), width, height);
    menu->createSlider(46*6,46*12,width, height, 46*2);
    menu->setSliderPosition(0.0f);
    
    //create button
    menu->addComponent(46*0, 46*15, 46, 46);
    //delete button
    menu->addComponent(46*1, 46*15, 46, 46);
    //join
    menu->addComponent(46*2, 46*15, 46, 46);
    //disjoin
    menu->addComponent(46*3, 46*15, 46, 46);
    //submit
    menu->addComponent(46*7, 46*15, 46, 46);

}

void initBoardUI(UI* board){
    SDL_Point center = board->getCenterOfUI();
    //TODO: I want to make it so that its adding each tile as its own component
    int tile_size = 120;
    int width = tile_size * 3;
    int height = tile_size * 3;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++ ){
            board->addComponent((center.x - width/2 + j*tile_size), (center.y - height/2 + i*tile_size), 120, 120);
        }
    }
    //board->addComponent(center.x - width/2, center.y - height/2, width , height);
    board->createSlider(46*6, 46*13, 40, 30, 46*2);
    board->setSliderPosition(0.0f);
}

void drawUI( SDL_Renderer* RENDERER,UI* ui,Board* board){
    for(int i = 0 ; i < ui->components.size(); i++){
        if(ui->last_selected_component == i){
            SDL_SetRenderDrawColor(RENDERER, 104, 4, 21, SDL_ALPHA_OPAQUE);
        }
        else if(board->active[i] == true){
            SDL_SetRenderDrawColor(RENDERER, 255,105,180,SDL_ALPHA_OPAQUE);
        }
        else{
            SDL_SetRenderDrawColor(RENDERER, 12, 4, 102, SDL_ALPHA_OPAQUE);
        }
        SDL_RenderFillRect(RENDERER, &ui->components[i].area);
    }
}

void drawButtons(SDL_Renderer* RENDERER, UI* control){
    //first button is create
    SDL_SetRenderDrawColor(RENDERER, 0, 233, 56, 255);
    SDL_RenderFillRect(RENDERER, &control->components[0].area);
    //second button is destroy
    SDL_SetRenderDrawColor(RENDERER, 233, 56, 0, 255);
    SDL_RenderFillRect(RENDERER, &control->components[1].area);
    //third is join
    SDL_SetRenderDrawColor(RENDERER, 148, 0, 211, 255);
    SDL_RenderFillRect(RENDERER, &control->components[2].area);
    //fourth is disjoin
    SDL_SetRenderDrawColor(RENDERER, 216, 191, 216, 255);
    SDL_RenderFillRect(RENDERER, &control->components[3].area);
    //fifth is submit
    SDL_SetRenderDrawColor(RENDERER, 212, 175, 55, 255);
    SDL_RenderFillRect(RENDERER, &control->components[4].area);
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


bool puzzle1(Board* model){
    
    printf("%d\n", model->size);
    int rvs = 1;
    
    float probs[rvs];
    float vals[rvs];
    bool found[rvs];
    //initialize solution
    for (int i = 0; i < rvs; i ++){
        found[i] = false;
    }
    if(model->size != rvs){
        return false;
    }
    //actual puzzle
    probs[0] = 0.5f;
    vals[0] = 1;
    
    //O(M + R) time, this could be cut down further but ill do that later
    for (int i = 0; i < model->bernoulis.size(); i++){
        for(int j = 0; j < rvs; j++){
            if(found[j]==false && probs[j] == model->bernoulis[i] && vals[j] == model->vals[i] ){
                found[j] = true;
            }
        }
    }
    
    
    for(int i = 0; i < rvs; i++){
        if (found[i] == false){
            return false;
        }
    }
    
    return true;
}

bool puzzle2(Board* model){
    int rvs = 2;
    
    float probs[rvs];
    float vals[rvs];
    bool found[rvs];
    //initialize solution
    for (int i = 0; i < rvs; i ++){
        found[i] = false;
    }
    if(model->size != rvs){
        return false;
    }
    //actual puzzle
    probs[0] = 0.5f;
    vals[0] = 1;
    probs[1] = 0.5f;
    vals[1] = 1;
    
    printf("\ninput size %d\n\n" , model->size);
    printf("input prob0 %f\n" , model->bernoulis[0]);
    printf("input val0 %f\n\n" , model->vals[0]);
    printf("input prob1 %f\n" , model->bernoulis[1]);
    printf("input val0 %f\n" , model->vals[1]);
    
    //O(M + R) time, this could be cut down further but ill do that later
    for (int i = 0; i < model->bernoulis.size(); i++){
        for(int j = 0; j < rvs; j++){
            if(found[j] == false && probs[j] == model->bernoulis[i] && vals[j] == model->vals[i] ){
                found[j] = true;
                break;
            }
        }
    }
    
    
    for(int i = 0; i < rvs; i++){
        if (found[i] == false){
            return false;
        }
    }
    
    return true;
    
}

const int aspect_tile_size = 46;

string getProbabilityString(UI* menu){
    stringstream ss;
    ss.precision(2);
    ss << "Probability: " << menu->getSliderPosition();
    return ss.str();
}

string getValueString(UI* menu){
    stringstream ss;
    ss.precision(2);
    ss << "Value: " << menu->getSliderPosition();
    return ss.str();
}

string getExpectationString(float val, float p){
    stringstream ss;
    ss.precision(2);
    ss << "E[X] ~ " << val*p;
    return ss.str();
}

string getTotalExpString(Board* model){
    stringstream ss;
    ss.precision(2);
    
    ss << "E'[";
    float total = 0;
    int count = 0;
    for (int i = 0; i < model->bernoulis.size(); i++){
        if(model->active[i]){
            if (count == 0){
                ss << "X_" << i;
                total += model->bernoulis[i] * model->vals[i];
                count++;
            }
            else{
                ss << "+" << "X_" << i;
                total += model->bernoulis[i] * model->vals[i];
                count++;
            }
            
        }
    }
    
    ss << "] ~ " << total;
    
    return ss.str();
}
//round the floating point input to 2 decimal places
float rounding(float input){
    return round(input * 100)/100;
}

SDL_Texture* loadTexture( SDL_Renderer* RENDERER, std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( RENDERER, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

vector<SDL_Rect> init_borders(){
    int top_y = 10;
    int bottom_y = 15;
    int left_x = 0;
    int right_x = 46*8;
    
    vector<SDL_Rect> temp;
    //col value
    for(int i = 0; i < 9; i++){
        SDL_Rect top = {i*46,top_y*46,46,46};
        SDL_Rect bot = {i*46,bottom_y*46, 46,46};
        
        temp.push_back(top);
        temp.push_back(bot);
    }
    
    //row val
    for(int i = top_y +  1; i < bottom_y ;i++){
        SDL_Rect left = {left_x,i*46, 46,46};
        SDL_Rect right = {right_x, i*46, 46, 46};
        
        temp.push_back(left);
        temp.push_back(right);
        
    }
    
    return temp;
}

void drawborder(SDL_Renderer* RENDERER, SDL_Texture* texture, vector<SDL_Rect> border_loc){
    for(int i = 0; i < border_loc.size(); i++){
        SDL_RenderCopy(RENDERER, texture, NULL, &border_loc[i]);
    }
}

int main(int argc, const char * argv[]) {
    
    int frame_time;
    int frame_start;
        
    //texture loading
    vector<SDL_Rect> animation;
    
    for (int i = 0; i < 5; i++){
        SDL_Rect temp = {i*46,0,46,46};
        animation.push_back(temp);
    }
    
    SDL_Rect filled_tiled = {5*46,0,46,46};
    
    vector<SDL_Rect> border_rects = init_borders();
    
    // insert code here...
    Core Core;
    Controller controller;
    Board model(36);
    UI board_control(0,aspect_tile_size*10,(aspect_tile_size*9),(aspect_tile_size*6));
    UI board_grid(0,0,aspect_tile_size*9,aspect_tile_size*10);
    
    initGameUI(&board_control);
    initBoardUI(&board_grid);
    
    TTF_Font* gFont = TTF_OpenFont("fonts/CaviarDreams.ttf", 24);

    SDL_Color white = {255,255,255};
    
    Texture text(0,46*12,60,60);
    Texture val(0,46*13,60,60);
    Texture exp(0,46*11, 60, 60);
    Texture exp2(0,46*10, 60, 60);
    
    //load large texture
    SDL_Texture* TILE_SPRITE_SHEET = loadTexture(Core.RENDERER, "tiles.bmp");
    SDL_Texture* border_texture = loadTexture(Core.RENDERER, "border_texture.bmp");
    SDL_Texture* slider = loadTexture(Core.RENDERER, "slider.bmp");

    bool win = false;
    
    int animation_test_count = 0;
    
    while(!controller.quit){
        frame_start = SDL_GetTicks();

        controller.pollEvents();
        
        //board update controller
        board_grid.mouseSelection(&controller);
        board_control.mouseSelection(&controller);

        //update ui
        board_control.setSliderPosition(model.bernoulis[board_grid.last_selected_component]);
        board_grid.setSliderPosition(model.vals[board_grid.last_selected_component]);
        
         //update slider
        if(board_control.slider.clicked > 0){
            board_control.updateSlider(controller.mPosition);
        }
        if(board_grid.slider.clicked > 0){
            board_grid.updateSlider(controller.mPosition);
        }
        //if active is clicked
        if(board_control.components[0].clicked > 0){
            model.activate(board_grid.last_selected_component);
        }
        //destroy 
        if(board_control.components[1].clicked > 0){
            model.deactivate(board_grid.last_selected_component);
        }
        //submit
        if(board_control.components[4].clicked > 0){
            win = puzzle2(&model);
            if(win){
                printf("Congratualtions! You completed the puzzle!\n");
                controller.quit = true;
            }
        }
        
        //update model
        model.updateBernouli(board_grid.last_selected_component, rounding(board_control.getSliderPosition()),rounding(board_grid.getSliderPosition()));
        
        //timah to dra
        SDL_SetRenderDrawColor(Core.RENDERER, 32, 98, 187, 12);
        SDL_RenderFillRect(Core.RENDERER, &board_control.Base);
        
        //draw sliders
        SDL_SetRenderDrawColor(Core.RENDERER, 254, 232, 87, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(Core.RENDERER, &board_control.slider.area);
        SDL_SetRenderDrawColor(Core.RENDERER, 30, 232, 87, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(Core.RENDERER, &board_grid.slider.area);
        
        //draw buttons
        drawButtons(Core.RENDERER, &board_control);
        
        SDL_SetRenderDrawColor(Core.RENDERER, 0, 130, 23, 30);
        SDL_RenderFillRect(Core.RENDERER, &board_grid.Base);
        
        drawUI(Core.RENDERER, &board_grid, &model);
        //draw 9:16 grid
        drawAspectRatioGrid(9,16,&Core);
        //slidershit
        text.textureFromString(Core.RENDERER, white, getProbabilityString(&board_control),gFont);
        val.textureFromString(Core.RENDERER, white, getValueString(&board_grid),gFont);
        exp.textureFromString(Core.RENDERER, white, getExpectationString(model.vals[board_grid.last_selected_component], model.bernoulis[board_grid.last_selected_component]),gFont);
        exp2.textureFromString(Core.RENDERER, white, getTotalExpString(&model),gFont);
        
        text.render(Core.RENDERER);
        val.render(Core.RENDERER);
        exp.render(Core.RENDERER);
        exp2.render(Core.RENDERER);

        //render texture on blocks
        //if the animation has started
        if(board_grid.components[0].clicked > 0){
            animation_test_count++;
        }
        if(animation_test_count > 0){
            if(animation_test_count > 20){
                animation_test_count = 0;
            }
            else{
                animation_test_count++;
            }
        }
        SDL_RenderCopy(Core.RENDERER, TILE_SPRITE_SHEET, &animation[animation_test_count%5], &board_grid.components[0].area);
        
        if(model.active[0] == true){
            SDL_RenderCopy(Core.RENDERER, border_texture, &filled_tiled, &board_grid.components[0].area);
        }
        
        drawborder(Core.RENDERER, border_texture, border_rects);
        
        SDL_RenderCopy(Core.RENDERER, slider, NULL, &board_grid.slider.area);
        
        SDL_RenderPresent(Core.RENDERER);
        
        SDL_RenderClear(Core.RENDERER);

        frame_time = SDL_GetTicks() - frame_start;
        if(FRAME_DELAY>frame_time){
            SDL_Delay(FRAME_DELAY-frame_time);
        }
    }
     
    return 0;
}
