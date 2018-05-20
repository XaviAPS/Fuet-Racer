#pragma once

#include "ofMain.h"
#include "MainMenu.hpp"
#include "Player.hpp"

#define NUM_BYTES 4 // Bytes to read
#define NUM_OBSTACLES 150

struct obstacle {
    float height;
    int lane;    //0 to 3
    bool isPerson;
};

enum gameState {
    menu, playing, paused
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        // Setup Components
        void setupPlayer();
        void setupMap();
        void setupMainMenu();

        // Update Components
		void updateMap();
		void checkCollisions();
		void explosion(float w, float h);

        // Draw Components
        void drawMap();
        void drawExplosions();

        // Ending related
        void drawVictory();
        void drawDefeat();
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
      gameState          state;

	    vector<obstacle>    obstacles, onScreenObstacles;
	    float               speed, initialSpeed, endingTimer;
		  int                 buttonValue, potentiometerMeanValue;
		  bool                sendSerialMessage, gameWin;
		  int                 countCycles;
		  ofSerial            serial;
      double             previousTime;
      double              elapsed_frames;

        // Explosion
        vector<ofImage>     explosionFrames;
        ofPoint             explodingPoint;
        int                 offset;
        float               explosionFPS;
        bool                isExpl, isFirstFrame;

        Player              player;
        ofImage             playerImage;
        MainMenu            mainMenu;
        ofImage             backgroundImage;


};
