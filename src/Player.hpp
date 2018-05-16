#pragma once

#include "ofMain.h"

class Player {
public:
    Player();
    void setup(ofImage * _img);
    void update();
    void draw();
    void reset();
    
public:

    ofPoint pos;
    ofImage *img;
    float width, height, speed;
    int lives;
    bool is_left_pressed, is_right_pressed, is_down_pressed, is_up_pressed;
};
