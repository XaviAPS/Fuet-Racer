//
//  MainMenu.cpp
//  Interactive Systems
//
//  Created by Jordan Pichler on 18/05/2018.
//

#include "MainMenu.hpp"

MainMenu::MainMenu() {}

MainMenu::MainMenu(ofImage *background) {
    this->background = background;
    
    carImage = ofImage("racecar_side.png");
    flagImage = ofImage("checkeredflag.png");
    
    verdana.loadFont("verdana.ttf", 32, true, true);
    verdana.setLineHeight(18.0f);
    verdana.setLetterSpacing(1.037);

}

void MainMenu::drawMenu() {
    background->draw(0, 0, ofGetWidth(), ofGetHeight());
    carImage.draw(ofGetWidth()/2 - carWidth/2,
                  ofGetHeight()/2 - carHeight/1.9,
                  carWidth, carHeight);
    
    float textWidth = verdana.stringWidth(menuText);
    verdana.drawString(menuText,
                       ofGetWidth()/2 - textWidth/2,
                       ofGetHeight()/2 + carHeight/1.2);
}

void MainMenu::drawVictory() {
    background->draw(0, 0, ofGetWidth(), ofGetHeight());
    flagImage.draw(ofGetWidth()/2 - flagWidth/2,
                   ofGetHeight()/2 - flagHeight/1.9,
                   flagWidth, flagHeight);
    
    float textWidth = verdana.stringWidth(victoryText);
    verdana.drawString(victoryText,
                       ofGetWidth()/2 - textWidth/2,
                       ofGetHeight()/2 + flagHeight/1.4);
    
}

void MainMenu::drawDefeat() {
    background->draw(0, 0, ofGetWidth(), ofGetHeight());
    float textWidth = verdana.stringWidth(defeatText);
    float textHeight = verdana.stringHeight(defeatText);

    verdana.drawString(defeatText,
                       ofGetWidth()/2 - textWidth/2,
                       ofGetHeight()/2 + textHeight/2);
    
}
