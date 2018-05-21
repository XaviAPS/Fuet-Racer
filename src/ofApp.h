#pragma once

#include "ofMain.h"
#include "MainMenu.hpp"
#include "Player.hpp"

#define NUM_BYTES 8 // Bytes to read
#define NUM_OBSTACLES 150

struct obstacle {
    float height;
    int lane;    //0 to 3
    bool isPerson;
};

struct explosion {
    float width;
    float height;
    float fps;
    bool isFirstFrame;
    bool endAnimation;
    int offset;
};

enum gameState {
    menu, playing, paused
};

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

        // Setup Components
        void setupPlayer();
        void setupMap();
        void setupMainMenu();

        // Update Components
		void updateMap(double elapsed_frames);
        void updateArduino(double elapsed_frames);
        void checkCollisions();
		void explosion(float w, float h);

        // Draw Components
        void drawMap();
        void drawExplosions(struct::explosion *o);

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

        vector<struct::obstacle>    obstacles, onScreenObstacles;
	    float               speed, initialSpeed, endingTimer;
        int                 buttonValue, luminosityMeanValue, potentiometerMeanValue;
        bool                sendSerialMessage, gameWin, isArduino;
        int                 countCycles;
        ofSerial            serial;
        double              previousTime, elapsed_frames;

        // Explosion
        vector<ofImage>     explosionFrames;
        vector<struct::explosion>   explodingPoints;
        float               explosionFPS;
        bool                isExpl, isFirstFrame;

        Player              player;
        ofImage             playerImage;
        MainMenu            mainMenu;
        ofImage             backgroundImage;
};
