#include <iostream>
#include "Core.hpp"
#include "Controller.hpp"
#include "Menu.hpp"
#include "Puzzle.hpp"

SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_DisplayMode gMode;
int normal_tile;

const int SCREEN_FPS = 15;
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

bool test1(){
    Board c2;
    int i = 4;

    int first_child = i-4;
    //if already in a chain we want to add to the tree
    //add piece to chain
    c2.parents[first_child] = i;
    c2.children[i][0] = first_child;
    c2.active[i] = true;
    c2.active[first_child] = true;
    c2.mode = 0;
    c2.chain_mode = false;
    //set values
    c2.bernoulis[i] = .7;
    //first child
    c2.bernoulis[first_child] = .8;
    c2.bernoulis2[first_child] = .1;
    //probability of parent happening if child happened
    c2.setEvidence(first_child);
    c2.setEvidence(first_child);
    
    printf("Answer .949152 result %f\n", c2.getProbChain(i));
    
    return true;
}

//2 children test
bool test2(){
    Board c2;
    int i = 4;
    
    
    int first_child = i-4;
    int second_child = i+1;
    //if already in a chain we want to add to the tree
    //add piece to chain
    c2.parents[first_child] = i;
    c2.children[i][0] = first_child;
    c2.active[i] = true;
    c2.active[first_child] = true;
    c2.mode = 0;
    c2.chain_mode = false;
    //set values
    c2.bernoulis[i] = .2;
    //first child
    c2.bernoulis[first_child] = .8;
    c2.bernoulis2[first_child] = .4;
    //probability of parent happening if child happened
    c2.setEvidence(first_child);
    c2.setEvidence(first_child);
    
    //second child
    c2.parents[second_child] = i;
    c2.children[i][3] = second_child;
    c2.active[i] = true;
    c2.active[second_child] = true;
    c2.mode = 0;
    c2.chain_mode = false;
    //set vals
    c2.bernoulis[second_child] = .9;
    c2.bernoulis2[second_child] = .1;
    c2.setEvidence(second_child);
    c2.setEvidence(second_child);
    
    printf("test 2 result %f\n", c2.getProbChain(i));
    
    return true;
}

bool test3(){
    Board c2;
    int i = 4;
    
    
    int first_child = i-4;
    int second_child = i+1;
    int third_child = i-1;
    //if already in a chain we want to add to the tree
    //add piece to chain
    c2.parents[first_child] = i;
    c2.children[i][0] = first_child;
    c2.active[i] = true;
    c2.active[first_child] = true;
    c2.mode = 0;
    c2.chain_mode = false;
    //set values
    c2.bernoulis[i] = 3.0/5.0;
    //first child
    c2.bernoulis[first_child] = 2.0/3.0;
    c2.bernoulis2[first_child] = .5;
    //probability of parent happening if child happened
    c2.setEvidence(first_child);
    c2.setEvidence(first_child);
    
    //second child
    c2.parents[second_child] = i;
    c2.children[i][3] = second_child;
    c2.active[i] = true;
    c2.active[second_child] = true;
    c2.mode = 0;
    c2.chain_mode = false;
    //set vals
    c2.bernoulis[second_child] = 2.0/3.0;
    c2.bernoulis2[second_child] = .5;
    c2.setEvidence(second_child);
    c2.setEvidence(second_child);
    
    //third child
    //second child
    
    c2.parents[third_child] = i;
    c2.children[i][2] = third_child;
    c2.active[i] = true;
    c2.active[third_child] = true;
    c2.mode = 0;
    c2.chain_mode = false;
    //set vals
    c2.bernoulis[third_child] = 1.0/3.0;
    c2.bernoulis2[third_child] = .5;
    c2.setEvidence(third_child);
    
    printf("test 3 result %f\n", c2.getProbChain(i));

    return true;
}

void puzzle1(Puzzle *p1){
    p1->ans.push_back(.5f);
    p1->ans2.push_back(0.0f);
    p1->evid.push_back(2);
    
    p1->ans.push_back(.5f);
    p1->ans2.push_back(.1f);
    p1->evid.push_back(0);
    
    p1->ans.push_back(.2f);
    p1->ans2.push_back(0.0f);
    p1->evid.push_back(2);
    
    char puzzler[1000] = "This is a test puzzle, what I want you to do is place one EVENT on the board. This event represents the probability of getting heads when flipping a coin.";
    p1->initPuzzleText(gRenderer, puzzler);
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
    
    //test3();
    
    //first
    puzzle1(&p1);
    
    
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
        //drawAspectRatio();
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
