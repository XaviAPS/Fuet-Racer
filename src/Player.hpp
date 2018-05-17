#pragma once

#include "ofMain.h"

class Player {

    public:
        Player();
        void setup(ofImage * _img);
        void update(double elapsed_secs);
        void draw();
        void windowResized(int w, int h);
        void reset();

        vector<ofPoint> lanePositions;
        ofPoint pos;
        ofImage *img;
        float width, height, speed,;
        int lives, startingLives, lane;
        bool is_left_pressed, is_right_pressed;
        double waitTime;
};
