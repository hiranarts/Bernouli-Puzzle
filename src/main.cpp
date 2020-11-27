#include <iostream>
#include "Core.hpp"
#include "Controller.hpp"
#include "Menu.hpp"
#include "Puzzle.hpp"

SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_DisplayMode gMode;
int normal_tile;

const int SCREEN_FPS = 30;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

void drawAspectRatio(){
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    for (int i = 0; i < 16; i ++){
        SDL_RenderDrawLine(gRenderer, 0, i*normal_tile, gMode.w, i*normal_tile);
    }
    for (int j = 0; j < 9; j++){
        SDL_RenderDrawLine(gRenderer, j*normal_tile, 0, j*normal_tile, gMode.h);
    }
}

//TODO: change this to drawVecRects
void drawLevels(Menu* menu){
    SDL_SetRenderDrawColor(gRenderer, 123, 32, 122, 255);
    for (int i = 0; i < menu->levels.size(); i++){
        SDL_RenderFillRect(gRenderer, &menu->levels[i]);
    }
}

int main(int argc, char *argv[]){
				
    
    SDL_Log("INIT success? : %d", init());
    setGlobalVariables();
    //Set this to set Global Vars
    //setGlobalWindow();
    Controller inputs;
    
    //Menu menu(gRenderer, &gMode,normal_tile,15);
    
    Puzzle p1;
    p1.init(&gMode, normal_tile);
    p1.initFont(normal_tile);
    
    int frame_start;
    int frame_current;
    
    while(!inputs.quit){
        
        //frame start
        frame_start = SDL_GetTicks();
        
        inputs.pollEvents(&gMode);
    
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear( gRenderer );
        
        p1.gameLoop(&inputs);

        p1.updateText(gRenderer);
        p1.render(gRenderer);
        
        
        //draw aspect ratio
        drawAspectRatio();
        //Update screen
        SDL_RenderPresent( gRenderer );
        
        //
        frame_current = SDL_GetTicks() - frame_start;
        
        if(frame_current < SCREEN_TICKS_PER_FRAME){
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_current);
        }
    }
    //SDL
    end();
    return 0;

}
