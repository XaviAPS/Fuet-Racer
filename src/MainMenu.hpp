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
    MainMenu(ofImage *background);
   
    // Make background interchangeable
    ofImage *background;

    string menuText =       "PRESS SPACE TO START";
    string victoryText =    "YOU WIN! :)";
    string defeatText =     "HAAA YOU SUCK!";
    
    void drawMenu();
    void drawVictory();
    void drawDefeat();

private:
    ofImage carImage;
    float carWidth = 560;
    float carHeight = 130;
    
    ofImage flagImage;
    float flagWidth = 400;
    float flagHeight = 320;
  
    ofTrueTypeFont verdana;
};
