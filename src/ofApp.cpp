#include "ofApp.h"

//-------------------- ALL HPlayer COMMANDS --------------------
//    /play [<path1>] [<path2>] ...       : Play the file (or dir) list in order
//    /playloop [<path1>] [<path2>] ...   : Same as play with playlist loop forced
//    /load [<path1>] [<path2>] ...       : Pre-Load a playlist
//    /volume <0:100>     : Set volume from 0 to 100
//    /blur <0:100>       : Set blur level from 0 to 100%
//    /zoom <0:100>       : Set zoom from 0 to 100%
//    /stop           : Stop and rewind the current playlist
//    /pause          : Pause the current file
//    /resume         : Resume the paused file
//    /next           : Play the next file in the list
//    /prev           : Play the previous file in the list
//    /mute           : Mute the sound
//    /unmute         : Unmute the sound
//    /loop           : Enable looping for the current playlist
//    /unloop         : Disable looping for the current playlist
//    /info           : Toggle media info window
//    /host <ip>      : Change IP for OSC out
//    /getStatus      : Ask for status info
//    /quit           : Exit the player
//--------------------------------------------------------------

void ofApp::setup(){

	ofBackground(40, 100, 40);
    
    pi1_ip = "192.168.0.101";
    pi2_ip = "192.168.0.102";
    pi3_ip = "192.168.0.103";
    pi4_ip = "192.168.0.104";
    
    iPiPort = 9000;
    
    folder_path1 = "/media/pi/usb1/";
    folder_path2 = "/media/pi/usb2/";
    folder_path3 = "/media/pi/usb3/";
    folder_path4 = "/media/pi/usb4/";
    
	// open outgoing connections
	sender1.setup(pi1_ip, iPiPort);
    sender2.setup(pi2_ip, iPiPort);
    sender3.setup(pi3_ip, iPiPort);
    sender4.setup(pi4_ip, iPiPort);
    
    soundPlayer.load("/Users/nicolai/Downloads/PERTURBATOR.mp3");
    
    //send random osc message to get HPlayer ready to receive other messages
    ofxOscMessage m;
    m.setAddress("/stop");
    sendMessageToAll(m);
    
    //make sure sound is set to 100%
    m.setAddress("/volume");
    m.addIntArg(100);
    sendMessageToAll(m);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(img.getWidth() > 0){
        ofDrawBitmapString("Image:", 10, 160);
        img.draw(10, 180);
    }
    
	// display instructions
	string buf;
	buf = "sending osc messages to " + pi1_ip + ":" + ofToString(iPiPort);
    int y = 20;
	ofDrawBitmapString(buf, 10, y);
    y += 30;
//	  ofDrawBitmapString("press A to send osc message [/test 1 3.5 hello <time>]", 10, 50);
//    y += 15;
    ofDrawBitmapString("press P to play all videos one shot", 10, y);
    y += 15;
    ofDrawBitmapString("press L to loop all videos", 10, y);
    y += 15;
    ofDrawBitmapString("press S to stop playing", 10, y);
    y += 15;
    ofDrawBitmapString("press N to start next video", 10, y);
    y += 15;
    ofDrawBitmapString("press B to go back to previous video", 10, y);
    y += 15;
    ofDrawBitmapString("press I to toggle info screen", 10, y);
    y += 15;
}

void ofApp::sendMessageToAll(ofxOscMessage m){
    sender1.sendMessage(m, false);
    sender2.sendMessage(m, false);
    sender3.sendMessage(m, false);
    sender4.sendMessage(m, false);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //play videos one shot(p) or in a loop(l)
    if(key == 'p' || key == 'P' || key == 'l' || key == 'L'){
        ofxOscMessage m;
        m.setAddress("/play");
        m.addStringArg(folder_path1);
        sendMessageToAll(m);
        if(key == 'p' || key == 'P'){
            ofxOscMessage m;
            m.setAddress("/unloop");
            sendMessageToAll(m);
        } else {
            ofxOscMessage m;
            m.setAddress("/loop");
            sendMessageToAll(m);
        }
        soundPlayer.play();
    }
    //stop playing
    if( key == 's' || key == 'S'){
        ofxOscMessage m;
        m.setAddress("/stop");
        sendMessageToAll(m);
        soundPlayer.stop();
    }
    //play next video
    if( key == 'n' || key == 'N'){
        ofxOscMessage m;
        m.setAddress("/next");
        sendMessageToAll(m);
        m.setAddress("/loop");
        sendMessageToAll(m);
    }
    //play previous video
    if( key == 'b' || key == 'B'){
        ofxOscMessage m;
        m.setAddress("/prev");
        sendMessageToAll(m);
        m.setAddress("/loop");
        sendMessageToAll(m);
    }
    //toggle info screen
    if( key == 'i' || key == 'I'){
        ofxOscMessage m;
        m.setAddress("/info");
        sendMessageToAll(m);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
//	ofxOscMessage m;
//	m.setAddress("/mouse/position");
//	m.addIntArg(x);
//	m.addIntArg(y);
//	sender1.sendMessage(m, false);
//  sender2.sendMessage(m, false);
//  sender3.sendMessage(m, false);
//  sender4.sendMessage(m, false);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
//	ofxOscMessage m;
//	m.setAddress("/mouse/button");
//	m.addIntArg(button);
//	m.addStringArg("down");
//    sender1.sendMessage(m, false);
//    sender2.sendMessage(m, false);
//    sender3.sendMessage(m, false);
//    sender4.sendMessage(m, false);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
//	ofxOscMessage m;
//	m.setAddress("/mouse/button");
//	m.addIntArg(button);
//	m.addStringArg("up");
//    sender1.sendMessage(m, false);
//    sender2.sendMessage(m, false);
//    sender3.sendMessage(m, false);
//    sender4.sendMessage(m, false);
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

