#include "Player.hpp"

Player::Player() {};

void Player::setup(ofImage * _img)
{
    img = _img;
    width = ofGetWidth()*100/1024;
    height= ofGetHeight()*100/768;
    speed = 5;
    startingLives = 5;
    lives = 5;
    startingMissiles = 3;
    missiles = 3;
    lane  = 2; // 0 to 3

    for(int i=1; i<5; i++) {
        ofPoint lanePoint;
        lanePoint.x = ofGetWidth()*0.2*i;
        lanePoint.y = ofGetHeight() - (ofGetHeight()*100/768);
        lanePoint.z = 0;
        lanePositions.push_back(lanePoint);
    }

    pos.x = lanePositions[lane].x;
    pos.y = lanePositions[lane].y;
    pos.z = 0;
    waitTime = 0;
}

void Player::reset() {
    speed = 5;
    lives = 5;
    lane  = 2;
}

void Player::switchToLane(int input_lane) {
    lane = input_lane;
    pos.x = lanePositions[lane].x;
}

void Player::update(double elapsed_frames) {
    // Position controllers
    waitTime-=elapsed_frames;
    if (is_left_pressed) {
        if(waitTime<0) {
            if(lane!=0) lane-=1;
            switchToLane(lane);
            waitTime = 0.2;
        }
    }
    if (is_right_pressed) {
        if(waitTime<0) {
            if(lane!=3) lane+=1;
            switchToLane(lane);
            waitTime = 0.2;
        }
    }
    if (is_up_pressed) {
        if(waitTime<0) {
            if(missiles>=1) {
                napalm = true;
            }
            waitTime = 0.2;
        }
    }
}

void Player::draw() {
    ofSetColor(255);
    img->draw(pos.x - width/2, pos.y - height/2, width, height);
}

void Player::windowResized(int w, int h) {
    // We need these to adapt car size and position
    // to screen-size changes
    lanePositions.clear();
    width = w*100/1024;
    height= h*100/768;
    for(int i=1; i<5; i++) {
        ofPoint lanePoint;
        lanePoint.x = w*0.2*i;
        lanePoint.y = h - (h*100/768);
        lanePoint.z = 0;
        lanePositions.push_back(lanePoint);
    }
}
