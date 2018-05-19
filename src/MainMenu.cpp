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
    verdana.loadFont("verdana.ttf", 30, true, true);
    verdana.setLineHeight(18.0f);
    verdana.setLetterSpacing(1.037);

}

void MainMenu::drawMenu() {
    background->draw(0, 0, ofGetWidth(), ofGetHeight());
   // carImage.draw(ofGetWidth()/2 - carWidth/2, ofGetHeight()/2 - carHeight/2, carWidth, carHeight);
    verdana.drawString("PRESS SPACE TO START", ofGetWidth()/2, 92);

}

void MainMenu::drawVictory() {
    background->draw(0, 0, ofGetWidth(), ofGetHeight());
    flagImage.draw(ofGetWidth()/2 - flagWidth/2,
                   ofGetHeight()/2 - flagHeight/2,
                   flagWidth, flagHeight);
    
    verdana.drawString("YOU WIN! :)", ofGetWidth()/2, ofGetHeight()/2 + flagHeight/1.5);
    
}

void MainMenu::drawDefeat() {
    background->draw(0, 0, ofGetWidth(), ofGetHeight());
    // carImage.draw(ofGetWidth()/2 - carWidth/2, ofGetHeight()/2 - carHeight/2, carWidth, carHeight);
    flagImage.draw(ofGetWidth()/2 - flagWidth/2, ofGetHeight()/2 - flagHeight/2, flagWidth, flagHeight);
    verdana.drawString("You Win! :)", ofGetWidth()/2, 92);
    
}
