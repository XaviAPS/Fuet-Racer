#include "ofApp.h"

// In this file we retrieve all inputs from arduino.
// My idea is to have a "player" class in a separate file.
// In this case, from here we should only have to trigger the right player's functions.

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);

	ofSetWindowPosition(75, 100);

	ofBackground(0);
	sendSerialMessage = false; //Variable to control the interval at which you read information from the Arduino

	serial.enumerateDevices(); //print all the devices
	serial.setup("COM5", 9600); //open the device at this address

	countCycles = 0;

    previousTime = clock();
    speed = 0.2;
	setupMap();
    setupPlayer();

}

void ofApp::setupPlayer() {
    playerImage.loadImage("racecar.png");
    player.setup(&playerImage);
}

void ofApp::setupMap() {
    srand(time(NULL));
    float currentHeight = -300;
    for(int i=0; i<NUM_OBSTACLES; i++) {
        obstacle obst;
        obst.height = currentHeight;
        obst.lane = (rand()%4);
        obst.isPerson = false;
        obstacles.push_back(obst);
        currentHeight-=((rand()%300)+200);
    }
}

//--------------------------------------------------------------
void ofApp::update() {

    clock_t currentTime = clock();
    elapsed_secs = double(currentTime - previousTime);
    updateMap();
    player.update(elapsed_secs);
    checkCollisions();
    previousTime = clock();
/*
	if (sendSerialMessage)
	{
		serial.writeByte('x'); //Send something to the Arduino to wake it up
		unsigned char bytesReturned[NUM_BYTES];

		memset(bytesReturned, 0, NUM_BYTES);//Set 0 for NUM_BYTES in bytesReturned

		while (serial.readBytes(bytesReturned, NUM_BYTES) > 0) { //While there's in receiving
		}

		// Here is where we should pay attention! We know that from Android's skecth we are sending
		// always 4 bytes, two for the potentiometer and two for the button, always sending first the
		// higher value bits of the 16 bits integers

		//Read info from the potentiometer
		potentiometerMeanValue = bytesReturned[0];
		potentiometerMeanValue <<= 8;
		potentiometerMeanValue += bytesReturned[1];

		//Read info from the button
		buttonValue = bytesReturned[2];
		buttonValue <<= 8;
		buttonValue += bytesReturned[3];

		sendSerialMessage = false;
	}
	// wait a 5 cycles before asking again since OF go faster than serial
	countCycles++;
	if (countCycles == 5)
	{
		sendSerialMessage = true;
		countCycles = 0;
	}
*/
}

void ofApp::updateMap() {
    int i,j=0;
    vector<obstacle>::iterator it;
    for(it = obstacles.begin(); it != obstacles.end(); ) {
        it->height+=(elapsed_secs*speed);
        if(it->height>0) {
            obstacle aux;
            aux.height = it->height;
            aux.lane = it->lane;
            aux.isPerson = it->isPerson;
            onScreenObstacles.push_back(aux);
            it = obstacles.erase(it);
        }
        else it++;
    }
    for(it = onScreenObstacles.begin(); it != onScreenObstacles.end(); ) {
        if(it->height>ofGetHeight()) it = onScreenObstacles.erase(it);
        else {
            it->height+=(elapsed_secs*speed);
            it++;
        }
    }
}

void ofApp::checkCollisions() {
    float playerTop = player.pos.y - player.height/2;
    float playerBot = player.pos.y + player.height/2;
    vector<obstacle>::iterator it;
    for(it = onScreenObstacles.begin(); it != onScreenObstacles.end(); ) {
        if(it->lane==player.lane) {
            if(it->height > playerTop && it->height < playerBot) {
                it = onScreenObstacles.erase(it);
            } else it++;
        } else it++;
    }
}

//--------------------------------------------------------------
void ofApp::draw() {

    drawMap();
    player.draw();

/*
    //original example
    int iRadius = 1;
	char tempStr[1024];

	float fRand = 0;
	for (int i = 0; i<ofGetWidth() + 1; i++)
	{
		//If the button is pressed we randomize color and make points bigger
		if (buttonValue)
		{
			iRadius = 5;
			ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
		}

		// We increase a variable depending on how open is the potentiometer, thus
		// each circle drawn more to the right will have a higher probability of
		// being away from the vertical center of the screen
		ofCircle(i, ((ofGetHeight() / 2) + ofRandom(-fRand, fRand)), iRadius);
		fRand += ofMap(potentiometerMeanValue, 0, 1023, 0, 0.2);
	}
*/
}

void ofApp::drawMap() {

    ofSetColor(255);
	int iWidth = ofGetWidth();
	int iHeight = ofGetHeight();
	int roadlineWidth = 2;

    //we draw borders
    ofRect(0, 0, iWidth/10, iHeight);
    ofRect(iWidth-(iWidth/10), 0, iWidth/10, iHeight);
    if(0.002*iWidth > 2) roadlineWidth = 0.002*iWidth;

    for(int i=1; i<4; i++) {
        for(int j=0; j<iHeight; j++) {
             ofCircle((iWidth/10) + (i*iWidth*0.2), j, roadlineWidth);
        }
    }

    //we draw obstacles
    float offsetWidth;
    vector<obstacle>::iterator it;
    for(it = onScreenObstacles.begin(); it != onScreenObstacles.end(); it++) {
        if(it->isPerson) ofSetColor(155);
        else ofSetColor(90);
        switch(it->lane) {
            case 0: offsetWidth = (iWidth*0.1 + iWidth*0.008); break;
            case 1: offsetWidth = (iWidth*0.3 + iWidth*0.008); break;
            case 2: offsetWidth = (iWidth*0.5 + iWidth*0.008); break;
            case 3: offsetWidth = (iWidth*0.7 + iWidth*0.008); break;
        }
        ofRect(offsetWidth, it->height, iWidth*0.18, iHeight*0.06);
    }
}

//-------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key==OF_KEY_LEFT)
        player.is_left_pressed = true;
    if(key==OF_KEY_RIGHT)
        player.is_right_pressed = true;
    if(key==OF_KEY_RETURN)
        playerImage.loadImage("nightcar.png");

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if(key==OF_KEY_LEFT)
        player.is_left_pressed = false;
    if(key==OF_KEY_RIGHT)
        player.is_right_pressed = false;
    if(key==OF_KEY_RETURN)
        playerImage.loadImage("racecar.png");
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

