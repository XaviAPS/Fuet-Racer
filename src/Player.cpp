#include "Player.hpp"

Player::Player() {};

void Player::setup(ofImage * _img)
{
    img = _img;
    width = ofGetWidth()*100/1024;
    height= ofGetHeight()*100/768;
    speed = 5;
    lives = 5;
    lane  = 2; // 0 to 3
    for(int i=1; i<5; i++) {
        ofPoint lanePoint;
        lanePoint.x = ofGetWidth()*0.2*i;
        lanePoint.y = ofGetHeight() - 100;
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

void Player::update(double elapsed_secs)
{
    waitTime-=elapsed_secs;
    //cout<<"time"<<waitTime<<endl;
    if(waitTime<0) {
        if (is_left_pressed) {
            if(lane!=0) lane-=1;
            else lives-=1;
            pos.x = lanePositions[lane].x;
            waitTime = 270;
        }
        if (is_right_pressed) {
            if(lane!=3) lane+=1;
            else lives-=1;
            pos.x = lanePositions[lane].x;
            waitTime = 270;
        }
    }
}

void Player::draw()
{
    ofSetColor(255);
    img->draw(pos.x - width/2, pos.y - height/2, width, height);
}
