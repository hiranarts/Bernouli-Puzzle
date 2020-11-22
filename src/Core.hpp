
#ifndef Core_hpp
#define Core_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>


extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_DisplayMode gMode;


extern int normal_tile;

bool initSDL();
bool initIMG();
bool initTTF();
bool init();
//exit out of all subsystems
void end();

void setGlobalVariables();
//tilesize is the length of a sqaure to the fit the aspect ratio r1:r2 of the device. It can be either 16:9 or 4:3
void setTileSize(int* size, int* r1, int* r2);

void setFont(TTF_Font* font, std::string path,int size);

void createTextureFromText(SDL_Renderer* r, SDL_Texture* texture, TTF_Font* font, std::string text);

#endif /* Board_hpp */

