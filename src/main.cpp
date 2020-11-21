#include <iostream>
#include "Core.hpp"
#include "Controller.hpp"

SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_DisplayMode gMode;
int normal_tile;

int main(int argc, char *argv[]){
				
    std::cout << "Herro Za WArudo" << std::endl;
    
    SDL_Log("INIT success? : %d", init());
    setGlobalVariables();
    //Set this to set Global Vars
    //setGlobalWindow();
    Controller inputs;
    SDL_Rect test = {0,0,30,40};
    
    
    while(!inputs.quit){
        inputs.pollEvents(&gMode);
        test.x = inputs.touchPosition.x;
        test.y = inputs.touchPosition.y;
        
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear( gRenderer );
        SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
        SDL_RenderFillRect(gRenderer, &test);
        //Update screen
        SDL_RenderPresent( gRenderer );
    }
     
    //SDL
    end();
    return 0;

}
