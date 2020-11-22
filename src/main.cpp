#include <iostream>
#include "Core.hpp"
#include "Controller.hpp"
#include "Menu.hpp"
SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_DisplayMode gMode;
int normal_tile;

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
				
    std::cout << "Herro Za WArudo" << std::endl;
    
    SDL_Log("INIT success? : %d", init());
    setGlobalVariables();
    //Set this to set Global Vars
    //setGlobalWindow();
    Controller inputs;
    Menu menu(gRenderer, &gMode,normal_tile,15);
    SDL_Rect test = {0,0,30,40};
    
    
    while(!inputs.quit){
        inputs.pollEvents(&gMode);
        test.x = inputs.touchPosition.x;
        test.y = inputs.touchPosition.y;
        
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear( gRenderer );
        SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
        SDL_RenderFillRect(gRenderer, &test);
        
        menu.game_title_text.render(0, 0);
        
        drawLevels(&menu);
        //draw aspect ratio
        drawAspectRatio();
        //Update screen
        SDL_RenderPresent( gRenderer );
    }
     
    //SDL
    end();
    return 0;

}
