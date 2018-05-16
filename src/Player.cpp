#include "Player.hpp"
Player::Player() {
}
void Player::setup(ofImage * _img)
{
    img = _img;
    pos.x = ofGetWidth() / 2;
    pos.y = ofGetHeight() - 100;
    width = 100;
    height= 100;
    speed = 5;
    lives = 5;
}
void Player::reset() {
    speed = 5;
    lives = 5;
}

/// 
void Player::update()
{
    if (is_left_pressed) {
        pos.x -= speed;
    }
    if (is_right_pressed) {
        pos.x += speed;
    }
    if (is_up_pressed) {
        pos.y -= speed;
    }
    if (is_down_pressed) {
        pos.y += speed;
    }
}

void Player::draw()
{
    img->draw(pos.x - width/2, pos.y - height/2 , width, height);
}
