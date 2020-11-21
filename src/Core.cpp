#include "Core.hpp"

bool initSDL(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		SDL_Log("SDL could not be initialized! Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

bool initIMG(){
	if (IMG_Init(IMG_INIT_PNG) < 0){
		SDL_Log("IMG could not be initialized! Error %s\n", SDL_GetError());
		return false;
	}
	return true;
}

bool initTTF(){
	if (TTF_Init() < 0){
		SDL_Log("TTF could not be initialized! Error %s\n", SDL_GetError());
		return false;
	} 
	return true;
}

bool init(){
	return initSDL() && initTTF() && initIMG();
}



void setGlobalVariables(){
    //set global gMode
    SDL_GetCurrentDisplayMode(0, &gMode);
    
    SDL_Log("\n%d,%d\n",gMode.w,gMode.h);
    
    //create window
    gWindow = SDL_CreateWindow("DBAYES", 0, 0, gMode.w, gMode.h, SDL_WINDOW_OPENGL || SDL_WINDOW_ALLOW_HIGHDPI);
    if (gWindow == NULL){
        SDL_Log("Window was not created!\n");
    }
    else{
        //create renderer
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == NULL){
            SDL_Log("Renderer was not created!\n");
        }
    }
    
    //set normal tile
    if(gMode.h/16 != gMode.w/9 ){
        SDL_Log("Dimension (height:%d,width:%d) can't be normalized 16:9\n", gMode.h, gMode.w);
        normal_tile = -1;
    }
    else{
        normal_tile = gMode.h/16;
    }
    
}

 

//TODO:
void end(){
    
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    
}


