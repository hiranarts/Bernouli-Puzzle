//
//  main.cpp
//  hamburger
//
//  Created by Ali Hamdani on 11/2/20.
//

#include <iostream>
#include "Core.hpp"
#include "Controller.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    Core Base;
    Controller controller;
    
    while(!controller.quit){
        controller.pollEvents();
        controller.printControl();
    }
    return 0;
}
