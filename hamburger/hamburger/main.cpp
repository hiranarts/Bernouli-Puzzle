//
//  main.cpp
//  hamburger
//
//  Created by Ali Hamdani on 11/2/20.
//

#include <iostream>
#include "Core.hpp"
#include "Controller.hpp"
#include "Board.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    Core Base;
    Controller controller;
    Board board;
    board.printRandomVariable(0, 0);
    /*
    while(!controller.quit){
        controller.pollEvents();
        //controller.printControl();
    }
     */
    return 0;
}
