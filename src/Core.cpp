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



void setFont(TTF_Font* font, std::string path, int size){
    font = TTF_OpenFont(path.c_str(), size);
    if(font == NULL){
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
}


void createTextureFromText(SDL_Renderer* r, SDL_Texture* texture, TTF_Font* font, std::string text){
    
    SDL_Color white = {255,255,255,255};
    SDL_Color black = {0, 0 ,0 , 255};
    
    //Free texture if it exists
    if( texture != NULL )
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), black);
       if( textSurface == NULL )
       {
           printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
       }
       else
       {
           //Create texture from surface pixels
           texture = SDL_CreateTextureFromSurface( r, textSurface );
           if( texture == NULL )
           {
               printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
           }
           //Get rid of old surface
           SDL_FreeSurface( textSurface );
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


