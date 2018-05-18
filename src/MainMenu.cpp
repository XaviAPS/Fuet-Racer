//
//  MainMenu.cpp
//  Interactive Systems
//
//  Created by Jordan Pichler on 18/05/2018.
//

#include "MainMenu.hpp"

MainMenu::MainMenu() {}

MainMenu::MainMenu(ofImage *background, string text) {
    this->background = background;
    this->text = text;
    carImage = ofImage("racecar_side.png");
    flagImage = ofImage("checkeredflag.png");
}

void MainMenu::draw() {
    background->draw(0, 0, ofGetWidth(), ofGetHeight());
   // carImage.draw(ofGetWidth()/2 - carWidth/2, ofGetHeight()/2 - carHeight/2, carWidth, carHeight);
    flagImage.draw(ofGetWidth()/2 - flagWidth/2, ofGetHeight()/2 - flagHeight/2, flagWidth, flagHeight);
}

