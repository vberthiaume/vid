#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(40, 100, 40);
    
    pi1_ip = "localhost";
    pi2_ip = "localhost";
    pi3_ip = "localhost";
    pi4_ip = "localhost";
    
    iPiPort = 9000;
    
    folder_path = "/home/pi/Desktop/";

	// open outgoing connections
	sender1.setup(pi1_ip, iPiPort);
    sender2.setup(pi1_ip, iPiPort);
    sender3.setup(pi1_ip, iPiPort);
    sender4.setup(pi1_ip, iPiPort);
    
    imgAsBuffer = ofBufferFromFile("of-logo.png", true);

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
	buf = "sending osc messages to " + pi1_ip + ofToString(iPiPort);
	ofDrawBitmapString(buf, 10, 20);
	ofDrawBitmapString("press A to send osc message [/test 1 3.5 hello <time>]", 10, 50);
    ofDrawBitmapString("press P to play all videos one shot [/play " + folder_path + "]", 10, 65);
    ofDrawBitmapString("press L to loop all videos [/playloop " + folder_path + "]", 10, 80);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'a' || key == 'A'){
		ofxOscMessage m;
		m.setAddress("/test");
		m.addIntArg(1);
		m.addFloatArg(3.5f);
		m.addStringArg("hello");
		m.addFloatArg(ofGetElapsedTimef());
		
        sender1.sendMessage(m, false);
        sender2.sendMessage(m, false);
        sender3.sendMessage(m, false);
        sender4.sendMessage(m, false);
	}
    
    //send an image. (Note: the size of the image depends greatly on your network buffer sizes - if an image is too big the message won't come through )

    if( key == 'p' || key == 'P'){
        ofxOscMessage m;
        m.setAddress("/play " + folder_path);
        sender1.sendMessage(m);
        sender2.sendMessage(m);
        sender3.sendMessage(m);
        sender4.sendMessage(m);
    }
    
    if( key == 'l' || key == 'L'){
        ofxOscMessage m;
        m.setAddress("/playloop " + folder_path);
        sender1.sendMessage(m);
        sender2.sendMessage(m);
        sender3.sendMessage(m);
        sender4.sendMessage(m);
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
//    sender2.sendMessage(m, false);
//    sender3.sendMessage(m, false);
//    sender4.sendMessage(m, false);
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

