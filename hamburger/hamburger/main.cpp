//
//  main.cpp
//  hamburger
//
//  Created by Ali Hamdani on 11/2/20.
//

#include <iostream>
#include "Core.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Core Base;
    bool done = false;
    
    SDL_Event e;
    while(!done){
        Base.GAME_WINDOW
        while( SDL_PollEvent( &e ) != 0 ){
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                done = true;
            }
        }
    }
    return 0;
}
