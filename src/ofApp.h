#pragma once

#include "ofMain.h"
#include "Player.hpp"

#define NUM_BYTES 4 // Bytes to read
#define NUM_OBSTACLES 100

struct obstacle {
    float height;
    int lane;    //0 to 3
    bool isPerson;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        // Setup Components
        void setupPlayer();
        void setupMap();

        // Update Components
		void updateMap();
		void checkCollisions();
		void explosion(float w, float h);

        // Draw Components
        void drawMap();
        void drawExplosions();

        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
	    vector<obstacle> obstacles, onScreenObstacles;
	    float            speed;
		int              buttonValue, potentiometerMeanValue;
		bool             sendSerialMessage, endGame;
		int              countCycles;
		ofSerial         serial;
        clock_t          previousTime;
        double           elapsed_secs;

        // Explosion
        vector<ofImage>  explosionFrames;
        ofPoint          explodingPoint;
        int              offset;
        float            explosionFPS;
        bool             isExpl, isFirstFrame;

        Player player;
        ofImage playerImage;

};
