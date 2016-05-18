#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	current_msg_string = 0;

	ofBackground(30, 30, 130);
    
#ifdef __APPLE__
    soundPlayers[0].load("/Users/nicolai/Downloads/audio1.wav");
    soundPlayers[1].load("/Users/nicolai/Downloads/audio2.wav");
    soundPlayers[2].load("/Users/nicolai/Downloads/audio3.wav");
    soundPlayers[3].load("/Users/nicolai/Downloads/audio4.wav");
    soundPlayers[4].load("/Users/nicolai/Downloads/audio5.wav");
    soundPlayers[5].load("/Users/nicolai/Downloads/audio6.wav");
#else
    //soundPlayers[0].load("/home/pi/Desktop/audio1.wav");
    //soundPlayers[1].load("/home/pi/Desktop/audio2.wav");
    //soundPlayers[2].load("/home/pi/Desktop/audio3.wav");
    //soundPlayers[3].load("/home/pi/Desktop/audio4.wav");
    //soundPlayers[4].load("/home/pi/Desktop/audio5.wav");
    //soundPlayers[5].load("/home/pi/Desktop/audio6.wav");
    
    soundPlayers[0].load("/media/pi/usb2/audio1.wav");
    soundPlayers[1].load("/media/pi/usb2/audio2.wav");
    soundPlayers[2].load("/media/pi/usb2/audio3.wav");
    soundPlayers[3].load("/media/pi/usb2/audio4.wav");
    soundPlayers[4].load("/media/pi/usb2/audio5.wav");
    soundPlayers[5].load("/media/pi/usb2/audio6.wav");

#endif
    
    m_bIsPlaying = false;
    m_bIsLooping = false;

}

//--------------------------------------------------------------
void ofApp::update(){

	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}

	// check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // check for mouse moved message
        if(m.getAddress() == "/play" || m.getAddress() == "/loop"){
            if (m.getAddress() == "/loop"){
                m_bIsLooping = true;
            } else {
                m_bIsPlaying = true;
                m_bIsLooping = false;
            }
            //TODO: use objects for sound players that set the flags intelligently
            soundPlayers[0].play();
            m_bPlayerStarted[0] = true;
        }
        
        if(m.getAddress() == "/stop"){
            m_bIsPlaying = false;
            m_bIsLooping = false;
            for (int i = 0; i<6; ++i){
                soundPlayers[i].stop();
                m_bPlayerDone[i] = false;
                m_bPlayerStarted[i] = false;
            }
        }
        printMsgs(m);
    }
    
    if (m_bIsPlaying || m_bIsLooping){
        
        //return if currently playing a sound
        if (soundPlayers[0].isPlaying() || soundPlayers[1].isPlaying() ||
            soundPlayers[2].isPlaying() || soundPlayers[3].isPlaying() ||
            soundPlayers[4].isPlaying() || soundPlayers[5].isPlaying() ){
            return;
        }
        
        //figure out which sound just finished playing
        if (m_bPlayerStarted[0]){
            m_bPlayerDone[0] = true;
            m_bPlayerStarted[0] = false;
        } else if (m_bPlayerStarted[1]){
            m_bPlayerDone[1] = true;
            m_bPlayerStarted[1] = false;
        } else if (m_bPlayerStarted[2]){
            m_bPlayerDone[2] = true;
            m_bPlayerStarted[2] = false;
        } else if (m_bPlayerStarted[3]){
            m_bPlayerDone[3] = true;
            m_bPlayerStarted[3] = false;
        } else if (m_bPlayerStarted[4]){
            m_bPlayerDone[4] = true;
            m_bPlayerStarted[4] = false;
        } else if (m_bPlayerStarted[5]){
            m_bPlayerDone[5] = true;
            m_bPlayerStarted[5] = false;
        }
        
        //cycle through m_bPlayerDone, starting at the end, then start the next one, or set m_bIsPlaying = false;
        if (m_bPlayerDone[5]){
            m_bIsPlaying = false;
            for (int i = 0; i<6; ++i){
                m_bPlayerDone[i]= false;
            }
            if (m_bIsLooping) {
                soundPlayers[0].play();
                m_bPlayerStarted[0] = true;
            }
        } else if (m_bPlayerDone[4]){
            soundPlayers[5].play();
            m_bPlayerStarted[5] = true;
        } else if (m_bPlayerDone[3]){
            soundPlayers[4].play();
            m_bPlayerStarted[4] = true;
        } else if (m_bPlayerDone[2]){
            soundPlayers[3].play();
            m_bPlayerStarted[3] = true;
        } else if (m_bPlayerDone[1]){
            soundPlayers[2].play();
            m_bPlayerStarted[2] = true;
        } else if (m_bPlayerDone[0]){
            soundPlayers[1].play();
            m_bPlayerStarted[1] = true;
        }
    }
}

void ofApp::printMsgs(ofxOscMessage &m){
    // unrecognized message: display on the bottom of the screen
    string msg_string;
    msg_string = m.getAddress();
    msg_string += ": ";
    for(int i = 0; i < m.getNumArgs(); i++){
        // get the argument type
        msg_string += m.getArgTypeName(i);
        msg_string += ":";
        // display the argument - make sure we get the right type
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msg_string += ofToString(m.getArgAsInt32(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msg_string += ofToString(m.getArgAsFloat(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
            msg_string += m.getArgAsString(i);
        }
        else{
            msg_string += "unknown";
        }
    }
    // add to the list of strings to display
    msg_strings[current_msg_string] = msg_string;
    timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
    current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
    // clear the next line
    msg_strings[current_msg_string] = "";
}


//--------------------------------------------------------------
void ofApp::draw(){

	string buf;
	buf = "listening for osc messages on port" + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);

	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
