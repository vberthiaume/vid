#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(40, 100, 40);
    
    pi1_ip = "192.168.0.101";
    pi2_ip = "192.168.0.102";
    pi3_ip = "192.168.0.103";
    pi4_ip = "192.168.0.104";
    
    iPiPort = 9000;
    
    folder_path = "/media/pi/OSX_extended_journaled/";

	// open outgoing connections
	sender1.setup(pi1_ip, iPiPort);
    sender2.setup(pi2_ip, iPiPort);
    sender3.setup(pi3_ip, iPiPort);
    sender4.setup(pi4_ip, iPiPort);
    
    soundPlayer.load("/Users/nicolai/Downloads/PERTURBATOR.mp3");
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
//    ofDrawBitmapString("press N to start next video", 10, y);
//    y += 15;
//    ofDrawBitmapString("press B to go back to previous video", 10, y);
//    y += 15;
    ofDrawBitmapString("press I to toggle info screen", 10, y);
    y += 15;
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//	if(key == 'a' || key == 'A'){
//		ofxOscMessage m;
//		m.setAddress("/test");
//		m.addIntArg(1);
//		m.addFloatArg(3.5f);
//		m.addStringArg("hello");
//		m.addFloatArg(ofGetElapsedTimef());
//		
//        sender1.sendMessage(m, false);
//        sender2.sendMessage(m, false);
//        sender3.sendMessage(m, false);
//        sender4.sendMessage(m, false);
//
//	}
    //play videos one shot(p) or in a loop(l)
    if(key == 'p' || key == 'P' || key == 'l' || key == 'L'){
        ofxOscMessage m;
        m.setAddress("/play");
        m.addStringArg(folder_path);
        sender1.sendMessage(m, false);
        sender2.sendMessage(m, false);
        sender3.sendMessage(m, false);
        sender4.sendMessage(m, false);
        
        if(key == 'p' || key == 'P'){
            ofxOscMessage m;
            m.setAddress("/unloop");
            sender1.sendMessage(m, false);
            sender2.sendMessage(m, false);
            sender3.sendMessage(m, false);
            sender4.sendMessage(m, false);
        }
        soundPlayer.play();
    }
    //stop playing
    if( key == 's' || key == 'S'){
        ofxOscMessage m;
        m.setAddress("/stop");
        sender1.sendMessage(m, false);
        sender2.sendMessage(m, false);
        sender3.sendMessage(m, false);
        sender4.sendMessage(m, false);
        soundPlayer.stop();
    }
//    //play next video
//    if( key == 'n' || key == 'N'){
//        ofxOscMessage m;
//        m.setAddress("/next");
//        sender1.sendMessage(m, false);
//        sender2.sendMessage(m, false);
//        sender3.sendMessage(m, false);
//        sender4.sendMessage(m, false);
//    }
//    //play previous video
//    if( key == 'b' || key == 'B'){
//        ofxOscMessage m;
//        m.setAddress("/prev");
//        sender1.sendMessage(m, false);
//        sender2.sendMessage(m, false);
//        sender3.sendMessage(m, false);
//        sender4.sendMessage(m, false);
//    }
    //toggle info screen
    if( key == 'i' || key == 'I'){
        ofxOscMessage m;
        m.setAddress("/info");
        sender1.sendMessage(m, false);
        sender2.sendMessage(m, false);
        sender3.sendMessage(m, false);
        sender4.sendMessage(m, false);
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

