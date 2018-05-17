#pragma once

#include "ofMain.h"
#include "Player.hpp"

#define NUM_BYTES 4 // Bytes to read
#define NUM_OBSTACLES 100

struct obstacle {
    float height;
    int lane;    //1,2,3,4
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

        // Draw Components
        void drawMap();

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
		bool             sendSerialMessage;
		int              countCycles;
		ofSerial         serial;
        clock_t          previousTime;
        double           elapsed_secs;

        Player player;
        ofImage playerImage;

};
