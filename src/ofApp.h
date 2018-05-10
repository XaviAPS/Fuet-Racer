#pragma once

#include "ofMain.h"

#define NUM_BYTES 4 // Bytes to read

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
		int             buttonValue, potentiometerMeanValue;
		bool            sendSerialMessage;
		int             countCycles;
		ofSerial        serial;
};
