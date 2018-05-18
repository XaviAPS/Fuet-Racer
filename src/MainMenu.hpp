//
//  MainMenu.hpp
//  Interactive Systems
//
//  Created by Jordan Pichler on 18/05/2018.
//

#pragma once

#include "ofMain.h"

class MainMenu {
public:
    MainMenu();
    MainMenu(ofImage *background, string text);
   
    // Make background interchangeable
    ofImage *background;

    string text;
    
    void draw();
private:
    ofImage carImage;
    float carWidth = 560;
    float carHeight = 130;
    
    ofImage flagImage;
    float flagWidth = 400;
    float flagHeight = 320;
  
    
    
};
