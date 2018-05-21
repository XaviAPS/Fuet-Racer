#include "ofApp.h"

// In this file we retrieve all inputs from arduino.
// My idea is to have a "player" class in a separate file.
// In this case, from here we should only have to trigger the right player's functions.

void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowPosition(75, 100);
	ofBackground(0);

	sendSerialMessage = false;  // Variable to control the interval at which you read information from the Arduino
	serial.enumerateDevices();  // print all the devices
	serial.setup("COM4", 9600); //open the device at this address

	countCycles = 0;

    state = playing;
    previousTime = ofGetElapsedTimef();
    initialSpeed = 180;
    speed = initialSpeed;

    gameWin = false;
    setupPlayer();
    setupMainMenu();
    setupMap();
}

void ofApp::setupMainMenu() {
    backgroundImage.loadImage("gradient.png");
    mainMenu = MainMenu(&backgroundImage);
    state = menu;
}

void ofApp::setupPlayer() {
    playerImage.loadImage("racecar.png");
    player.setup(&playerImage);
}

void ofApp::setupMap() {
    srand(time(NULL));
    float currentHeight = -300;
    float minDistance = player.height + (ofGetHeight()* 0.1);
    for(int i=0; i<NUM_OBSTACLES; i++) {
        struct::obstacle obst;
        obst.height = currentHeight;
        obst.lane = (rand()%4);
        obst.isPerson = false;
        obstacles.push_back(obst);
        currentHeight-=((rand()%300)+minDistance);
    }

    // Load explosion images & timers
    ofDirectory dir;
    int nFiles = dir.listDir("explosion");
    for(int i=0; i<dir.numFiles(); i++) {
        string filePath = dir.getPath(i);
        explosionFrames.push_back(ofImage());
        explosionFrames.back().loadImage(filePath);
    }
    explosionFPS = 12;
    isFirstFrame = false;
    isExpl = false;
}

void ofApp::update() {
    double currentTime = ofGetElapsedTimef();
    elapsed_frames = currentTime - previousTime;

    if((player.lives<=0)||gameWin) {
        exit();
        endingTimer+=elapsed_frames;
        if(endingTimer>300) ofExit();
    } else {
        updateMap(elapsed_frames);
        player.update(elapsed_frames);
        checkCollisions();
    }
    previousTime = ofGetElapsedTimef();

	if (sendSerialMessage) {
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

        //Read info from the light sensor
		luminosityMeanValue = bytesReturned[4];
		luminosityMeanValue <<= 8;
		luminosityMeanValue += bytesReturned[5];

		sendSerialMessage = false;

        // FIXMME: This hits performance...

        //Potentiometer check
        if(potentiometerMeanValue <= 256 and potentiometerMeanValue >= 10)
        {
            player.switchToLane(0);

        }

        else if(potentiometerMeanValue <= 512 and potentiometerMeanValue >= 257)
        {
            player.switchToLane(1);
        }


        else if(potentiometerMeanValue <= 768 and potentiometerMeanValue >= 513)
        {
            player.switchToLane(2);
        }

        else if(potentiometerMeanValue <= 1020 and potentiometerMeanValue >= 769)
        {
            player.switchToLane(3);
        }

        if (luminosityMeanValue < 512) {
            playerImage.loadImage("nightcar.png");
        } else {
            playerImage.loadImage("racecar.png");

        }

		if(buttonValue) {
            player.napalm = true;
        } else {
            player.napalm = false;
        }



	}
	// wait a 5 cycles before asking again since OF go faster than serial
	countCycles++;
//	cout<<potentiometerMeanValue<<endl;
	if (countCycles == 5)
	{
		sendSerialMessage = true;
		countCycles = 0;
	}
}

void ofApp::updateMap(double elapsed_frames) {
    int i,j=0;
    vector<struct::obstacle>::iterator it;
    for(it = obstacles.begin(); it != obstacles.end(); ) {
        it->height+=(elapsed_frames*speed);
        if(it->height+(ofGetHeight()*0.06)>0) {
            struct::obstacle aux;
            aux.height = it->height;
            aux.lane = it->lane;
            aux.isPerson = it->isPerson;
            onScreenObstacles.push_back(aux);
            it = obstacles.erase(it);
        }
        else it++;
    }

    for(it = onScreenObstacles.begin(); it != onScreenObstacles.end(); ) {
        if(player.napalm == true) {
            if(it->lane == player.lane) {
                struct::explosion auxPoint;
                auxPoint.width = player.pos.x;
                auxPoint.height = it->height;
                auxPoint.fps = explosionFPS;
                auxPoint.isFirstFrame = true;
                auxPoint.endAnimation = false;
                explodingPoints.push_back(auxPoint);
                it = onScreenObstacles.erase(it);
            }
            else it++;
        }
        else if(it->height>ofGetHeight()) {
            it = onScreenObstacles.erase(it);
            if(speed<230) speed = speed*1.056;
            else if(speed<270) speed = speed*1.028;
            else speed = speed*1.014;
        } else {
            it->height+=(elapsed_frames*speed);
            it++;
        }
    }
    player.napalm = false;
    
    // delete explosions after they spent their animation timer
    vector<struct::explosion>::iterator ip;
    for(ip = explodingPoints.begin(); ip != explodingPoints.end(); ) {
        if(ip->endAnimation) ip = explodingPoints.erase(ip);
        else ip++;
    }
    if(obstacles.size()==0) {
        if(onScreenObstacles.size()==0) gameWin = true;
    }
}

void ofApp::checkCollisions() {
    float playerTop = player.pos.y - player.height/2;
    float playerBot = player.pos.y + player.height/2;
    vector<struct::obstacle>::iterator it;
    for(it = onScreenObstacles.begin(); it != onScreenObstacles.end(); ) {
        if(it->lane==player.lane) {
            if(it->height > playerTop && it->height < playerBot) {
                struct::explosion auxPoint;
                it = onScreenObstacles.erase(it);
                player.lives--;
                auxPoint.width = player.pos.x;
                auxPoint.height = player.pos.y;
                auxPoint.fps = explosionFPS;
                auxPoint.isFirstFrame = true;
                auxPoint.endAnimation = false;
                explodingPoints.push_back(auxPoint);
            } else it++;
        } else it++;
    }
}

void ofApp::draw() {
    if (state == menu) {
        mainMenu.drawMenu();
        return;
    }

    // End game conditions
    if(gameWin) {
        mainMenu.drawVictory();
    }

    else if(player.lives<=0) mainMenu.drawDefeat();

    // Game loop
    else {
        drawMap();
        player.draw();
        vector<struct::explosion>::iterator it;
        for(it = explodingPoints.begin(); it != explodingPoints.end(); it++) {
            drawExplosions(&(*it));
        }
    }
}

void ofApp::drawMap() {

    ofSetColor(255);
	int iWidth = ofGetWidth();
	int iHeight = ofGetHeight();
	int roadlineWidth = 2;

    //we draw borders
    ofRect(0, 0, iWidth*0.1, iHeight);
    ofRect(iWidth-(iWidth*0.1), 0, iWidth*0.1, iHeight);
    if(0.002*iWidth > 2) roadlineWidth = 0.002*iWidth;

    for(int i=1; i<4; i++) {
        for(int j=0; j<iHeight; j++) {
             ofCircle((iWidth*0.1) + (i*iWidth*0.2), j, roadlineWidth);
        }
    }

    //we draw obstacles
    float speedRate = ((speed - initialSpeed)/initialSpeed)*0.5;
    float offsetWidth;
    vector<struct::obstacle>::iterator it;
    for(it = onScreenObstacles.begin(); it != onScreenObstacles.end(); it++) {
        if(it->isPerson) ofSetColor(155);
        else ofSetColor(speedRate*255,abs(127-(speedRate*255)),255-(speedRate*(255/2)));
        switch(it->lane) {
            case 0: offsetWidth = (iWidth*0.1 + iWidth*0.008); break;
            case 1: offsetWidth = (iWidth*0.3 + iWidth*0.008); break;
            case 2: offsetWidth = (iWidth*0.5 + iWidth*0.008); break;
            case 3: offsetWidth = (iWidth*0.7 + iWidth*0.008); break;
        }
        ofRect(offsetWidth, it->height, iWidth*0.18, iHeight*0.06);
    }

    // we draw lives
    ofSetColor(220,20,60);
    for(int i=0; i<player.lives; i++) {
        ofCircle(iWidth*0.05, (iHeight*0.05)+(iHeight*i*0.04), 9.5);
    }
    ofSetColor(204);
    for(int i=player.startingLives; i>player.lives; i--) {
        ofCircle(iWidth*0.05, (iHeight*0.05)+(iHeight*(i-1)*0.04), 9.5);
    }

    // we draw missiles
    ofSetColor(233,100,0);
    for(int i=0; i<player.missiles; i++) {
        ofCircle(iWidth*0.95, (iHeight*0.05)+(iHeight*i*0.04), 9.5);
    }
    ofSetColor(204);
    for(int i=player.startingMissiles; i>player.missiles; i--) {
        ofCircle(iWidth*0.95, (iHeight*0.05)+(iHeight*(i-1)*0.04), 9.5);
    }
}

void ofApp::drawExplosions(struct::explosion *o) {
    int frameIndex = (int)(ofGetElapsedTimef() * explosionFPS) % explosionFrames.size();
    if(o->isFirstFrame) {
        o->offset = 9 - frameIndex;
        o->isFirstFrame = false;
        //cout<<"in "<<o->offset<<" "<<frameIndex<<endl;
    }
    frameIndex = (frameIndex + o->offset) % explosionFrames.size();
    cout<<frameIndex<<endl;
    int width = ofGetWidth()*172/1024;
    int height= ofGetHeight()*172/768;
    ofSetColor(255);
    explosionFrames[frameIndex].draw(o->width-width/2,o->height-height/2,width,height);
    if(frameIndex==8) o->endAnimation = true;
}

void ofApp::keyPressed(int key) {
    if(key==OF_KEY_LEFT)
        player.is_left_pressed = true;
    if(key==OF_KEY_RIGHT)
        player.is_right_pressed = true;
   /* if(key==OF_KEY_UP)
        player.is_up_pressed = true;*/
    if(key==OF_KEY_RETURN)
        playerImage.loadImage("nightcar.png");
}

void ofApp::keyReleased(int key) {
    if(key==OF_KEY_LEFT)
        player.is_left_pressed = false;
    if(key==OF_KEY_RIGHT)
        player.is_right_pressed = false;
    if(key==OF_KEY_RETURN)
        playerImage.loadImage("racecar.png");
    if(key==' ')
        state = playing;
}

void ofApp::mouseMoved(int x, int y) {

}

void ofApp::mouseDragged(int x, int y, int button) {

}

void ofApp::mousePressed(int x, int y, int button) {

}

void ofApp::mouseReleased(int x, int y, int button) {

}

void ofApp::windowResized(int w, int h) {
    player.windowResized(w, h);
}

void ofApp::gotMessage(ofMessage msg) {

}

void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::exit() {
    player.lanePositions.clear();
    obstacles.clear();
    onScreenObstacles.clear();
}
