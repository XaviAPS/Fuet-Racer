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
        void switchToLane(int lane);

        vector<ofPoint> lanePositions;
        ofPoint pos;
        ofImage *img;
        float width, height, speed;
        int lives, startingLives, missiles, startingMissiles, lane;
        bool is_left_pressed, is_right_pressed, is_up_pressed, napalm;
        double waitTime;
};
