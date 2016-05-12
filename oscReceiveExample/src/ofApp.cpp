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
    
    soundPlayers[0].load("/home/pi/Desktop/audio1.wav");
    soundPlayers[1].load("/home/pi/Desktop/audio2.wav");
    soundPlayers[2].load("/home/pi/Desktop/audio3.wav");
    soundPlayers[3].load("/home/pi/Desktop/audio4.wav");
    soundPlayers[4].load("/home/pi/Desktop/audio5.wav");
    soundPlayers[5].load("/home/pi/Desktop/audio6.wav");
#endif
    
    m_bIsPlaying = false;

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
        if(m.getAddress() == "/play"){
            m_bIsPlaying = true;
            soundPlayers[0].play();
        }
        //            soundPlayer.stop();
        printMsgs(m);
    }
    
    if (m_bIsPlaying){
        if (!m_bPlayerDone[0] && !soundPlayers[0].isPlaying()){
            m_bPlayerDone[0] = true;
            soundPlayers[1].play();
        }
        
        else if (!m_bPlayerDone[1] && !soundPlayers[1].isPlaying()){
            m_bPlayerDone[1] = true;
            soundPlayers[2].play();
        }

        else if (m_bPlayerDone[1] && !soundPlayers[2].isPlaying()){
            m_bIsPlaying = false;
            for (int i = 0; i<6; ++i){
                m_bPlayerDone[i]= false;
            }
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
