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


//taken from http://stackoverflow.com/questions/236129/split-a-string-in-c
#include <sstream>
#include <vector>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void ofApp::setup(){

	ofBackground(25, 25, 25);
    
    pi1_ip = "192.168.0.101";
    pi2_ip = "192.168.0.102";//"192.168.1.107";
    pi3_ip = "192.168.0.103";
    pi4_ip = "192.168.0.104";
    local_ip ="127.0.0.1";
    
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
    senderLocal.setup(local_ip, iPiPort);
    
//    soundPlayer.load("/Users/nicolai/Downloads/PERTURBATOR.mp3");
    
    //send random osc message to get HPlayer ready to receive other messages
//    ofxOscMessage m;
//    m.setAddress("/stop");
//    sendMessageToAll(m);
    
    filesToPlayTextInput = new ofxDatGuiTextInput("Files to play/loop", "");
    filesToPlayTextInput->onTextInputEvent(this, &ofApp::onTextInputEvent);
    filesToPlayTextInput->setWidth(300, .4);
    
    playButton = new ofxDatGuiButton("PLAY ONCE");
    playButton->setWidth(75);
    loopButton = new ofxDatGuiButton("LOOP");
    loopButton->setWidth(50);
    
    playButton->onButtonEvent(this, &ofApp::onButtonEvent);
    loopButton->onButtonEvent(this, &ofApp::onButtonEvent);
}

void ofApp::setVolumeToMax(){
    //make sure sound is set to 100%
    ofxOscMessage m;
    m.setAddress("/volume");
    m.addIntArg(100);
    sendMessageToAll(m);
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    playList = split(e.text, ',');
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target == playButton || e.target == loopButton){
        setVolumeToMax();
        
        if (playList.size() != 0){
            ofxOscMessage m1, m2, m3, m4;
            if (e.target == playButton){
                cout << "play\n";
//                ofxOscMessage m;
//                m.setAddress("/unloop");
//                sendMessageToAll(m);
                m1.setAddress("/play");
                m2.setAddress("/play");
                m3.setAddress("/play");
                m4.setAddress("/play");
            } else if (e.target == loopButton){
                cout << "loop\n";
//                ofxOscMessage m;
//                m.setAddress("/loop");
//                sendMessageToAll(m);
                m1.setAddress("/playloop");
                m2.setAddress("/playloop");
                m3.setAddress("/playloop");
                m4.setAddress("/playloop");
            }
            for(auto& video : playList){
                if (video == "1"){
                    cout << "1\n";
                    m1.addStringArg(folder_path1+"video1.mov");
                    m2.addStringArg(folder_path2+"video1.mov");
                    m3.addStringArg(folder_path3+"video1.mov");
                    m4.addStringArg(folder_path4+"video1.mov");
                } else if (video == "2"){
                    cout << "2\n";
                    m1.addStringArg(folder_path1+"video2.mp4");
                    m2.addStringArg(folder_path2+"video2.mp4");
                    m3.addStringArg(folder_path3+"video2.mp4");
                    m4.addStringArg(folder_path4+"video2.mp4");
                } else if (video == "3"){
                    cout << "3\n";
                    m1.addStringArg(folder_path1+"video3.mp4");
                    m2.addStringArg(folder_path2+"video3.mp4");
                    m3.addStringArg(folder_path3+"video3.mp4");
                    m4.addStringArg(folder_path4+"video3.mp4");
                } else if (video == "4"){
                    cout << "4\n";
                    m1.addStringArg(folder_path1+"video4.mp4");
                    m2.addStringArg(folder_path2+"video4.mp4");
                    m3.addStringArg(folder_path3+"video4.mp4");
                    m4.addStringArg(folder_path4+"video4.mp4");
                } else if (video == "5"){
                    cout << "5\n";
                    m1.addStringArg(folder_path1+"video5.mp4");
                    m2.addStringArg(folder_path2+"video5.mp4");
                    m3.addStringArg(folder_path3+"video5.mp4");
                    m4.addStringArg(folder_path4+"video5.mp4");
                } else if (video == "6"){
                    cout << "6\n";
                    m1.addStringArg(folder_path1+"video6.mp4");
                    m2.addStringArg(folder_path2+"video6.mp4");
                    m3.addStringArg(folder_path3+"video6.mp4");
                    m4.addStringArg(folder_path4+"video6.mp4");
                }
            }
            sender1.sendMessage(m1, false);
            sender2.sendMessage(m2, false);
            sender3.sendMessage(m3, false);
            sender4.sendMessage(m4, false);
            senderLocal.sendMessage(m1, false);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    filesToPlayTextInput->update();
    playButton->update();
    loopButton->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(img.getWidth() > 0){
        ofDrawBitmapString("Image:", 10, 160);
        img.draw(10, 180);
    }
    
	// display instructions
    int x = 10;
    int y = 20;
	string buf;
	buf = "WELCOME TO BARBARA'S INSTALLATION";
	ofDrawBitmapString(buf, x, y);
    y += 30;
    ofDrawBitmapString("press 'p' to play all videos one shot", x, y);
    y += 15;
    ofDrawBitmapString("press 'l' to loop all videos", x, y);
    y += 15;
    ofDrawBitmapString("press 's' to stop playing", x, y);
    y += 15;
    ofDrawBitmapString("press 'n' to play next video", x, y);
    y += 15;
    ofDrawBitmapString("press 'b' to go back to previous video", x, y);
    y += 15;
    ofDrawBitmapString("press 'i' to toggle info screen", x, y);
    y += 15;
    ofDrawBitmapString("press 'Q' to quit HPlayer", x, y);
    y += 15;
    filesToPlayTextInput->setPosition(x, y);
    filesToPlayTextInput->draw();
    
    playButton->setPosition(x+300+5, y);
    loopButton->setPosition(x+300+5+75+5, y);
    playButton->draw();
    loopButton->draw();
}

void ofApp::sendMessageToAll(ofxOscMessage m){
    sender1.sendMessage(m, false);
    sender2.sendMessage(m, false);
    sender3.sendMessage(m, false);
    sender4.sendMessage(m, false);
    senderLocal.sendMessage(m, false);
}

void ofApp::playAllVideos(){
    {
        ofxOscMessage m;
        m.setAddress("/play");
        m.addStringArg(folder_path1);
        sender1.sendMessage(m, false);
        senderLocal.sendMessage(m, false);
    }
    {
        ofxOscMessage m;
        m.setAddress("/play");
        m.addStringArg(folder_path2);
        sender2.sendMessage(m, false);
    }
    {
        ofxOscMessage m;
        m.setAddress("/play");
        m.addStringArg(folder_path3);
        sender3.sendMessage(m, false);
    }
    {
        ofxOscMessage m;
        m.setAddress("/play");
        m.addStringArg(folder_path4);
        sender4.sendMessage(m, false);
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //play videos one shot(p) or in a loop(l)
    if(key == 'p' || key == 'P' || key == 'l' || key == 'L'){
        playAllVideos();
        if(key == 'p' || key == 'P'){
            ofxOscMessage m;
            m.setAddress("/unloop");
            sendMessageToAll(m);
        } else {
            ofxOscMessage m;
            m.setAddress("/loop");
            sendMessageToAll(m);
        }
//        soundPlayer.play();
    }
    //stop playing
    if( key == 's' || key == 'S'){
        ofxOscMessage m;
        m.setAddress("/stop");
        sendMessageToAll(m);
//        soundPlayer.stop();
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
    //quit HPlayer
    if( key == 'Q'){
        ofxOscMessage m;
        m.setAddress("/quit");
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

