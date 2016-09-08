#include "ofApp.h"

//-------------------- ALL HPlayer OSC COMMANDS --------------------
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
//--------------------------------------------------------------

void ofApp::setup(){

	ofBackground(25, 25, 25);
    ofSetFrameRate(20);
    m_bLooping = false;
    
    //All IP addresses
    pi1_ip = "192.168.0.101";
    pi2_ip = "192.168.0.102";
    pi3_ip = "192.168.0.103";
    pi4_ip = "192.168.0.104";
    
    //OSC Ports
    iPiVideoPort = 9000;
    
#if AUDIO_OSCRECEIVER_MAC
    local_ip ="127.0.0.1";
    iPiAudioPort = 9500;
    senderLocal.setup(local_ip, iPiAudioPort);
#endif
    
    boilerplate();
}

//void ofApp::setVolumeToMax(){
//    //make sure sound is set to 100%
//    ofxOscMessage m;
//    m.setAddress("/volume");
//    m.addIntArg(100);
//    sendMessageToAll(m);
//}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e) {
    playList = split(e.text, ',');
}

void ofApp::keyPressed(int key){
    //play videos one shot(p) or in a loop(l)
//    if(key == 'p' || key == 'P' || key == 'l' || key == 'L'){
//        playAllVideos();
//        if(key == 'p' || key == 'P'){
//            ofxOscMessage m;
//            m.setAddress("/unloop");
//            sendMessageToAll(m);
//        } else {
//            ofxOscMessage m;
//            m.setAddress("/loop");
//            sendMessageToAll(m);
//        }
//        //        soundPlayer.play();
//    }
    if(key == 'p' || key == 'P'){
        playAllVideos();
    }
    
    if(key == 'l' || key == 'L'){
        ofxOscMessage m;
        m_bLooping = !m_bLooping;
        if (m_bLooping){
            m.setAddress("/loop");
        } else {
            m.setAddress("/unloop");
        }
        sendMessageToAll(m);
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
//        m.setAddress("/loop");
//        sendMessageToAll(m);
    }
    //play previous video
    if( key == 'b' || key == 'B'){
        ofxOscMessage m;
        m.setAddress("/prev");
        sendMessageToAll(m);
//        m.setAddress("/loop");
//        sendMessageToAll(m);
    }
    //toggle info screen
    if(key == 'i' || key == 'I'){
        ofxOscMessage m;
        m.setAddress("/info");
        sendMessageToAll(m);
    }
    //quit HPlayer
    if(key == 'Q'){
        ofxOscMessage m;
        m.setAddress("/quit");
        sendMessageToAll(m);
    }
    if(key == 'a'){
        ofxOscMessage m;
        m.setAddress("/getStatus");
        sendMessageToAll(m);
    }
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e) {
    if (e.target == playButton || e.target == loopButton){
//        setVolumeToMax();
        if (playList.size() != 0){
            
            
#if MAC_PLAYS_AUDIO
            ofxOscMessage m;
            m.setAddress("/unloop");
            sendMessageToAll(m);
            for(auto& video : playList){
                playWithAudioThenStop(video);
            }
#else
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
                    m1.addStringArg(folder_path1+"video1.mp4");
                    m2.addStringArg(folder_path2+"video1.mp4");
                    m3.addStringArg(folder_path3+"video1.mp4");
                    m4.addStringArg(folder_path4+"video1.mp4");
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
            sender1video.sendMessage(m1, false);
            sender2.sendMessage(m2, false);
            sender3.sendMessage(m3, false);
            sender4.sendMessage(m4, false);
#if AUDIO_OSCRECEIVER_MAC
            senderLocal.sendMessage(m1, false);
#endif  //AUDIO_OSCRECEIVER_MAC
#endif  //MAC_PLAYS_AUDIO
        }
    }
}



void ofApp::sendMessageToAll(ofxOscMessage m){
    sender1video.sendMessage(m, false);
    sender2.sendMessage(m, false);
    sender3.sendMessage(m, false);
    sender4.sendMessage(m, false);
#if AUDIO_OSCRECEIVER_MAC
    senderLocal.sendMessage(m, false);
#endif
}


void ofApp::playAllVideos(){
    {
        ofxOscMessage m;
        m.setAddress("/play");
        m.addStringArg(folder_path1);
        sender1video.sendMessage(m, false);
#if AUDIO_OSCRECEIVER_MAC
        senderLocal.sendMessage(m, false);
#endif
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
void ofApp::update(){
    filesToPlayTextInput->update();
    playButton->update();
    loopButton->update();
    
    // hide old osc messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
    
    // check for waiting osc messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        printMsgs(m);
    }
}

void ofApp::printMsgs(ofxOscMessage &m){
    
    bool DISPLAY_ALL = false;
    
    string msg_string;
    msg_string = "IP: " + m.getRemoteIp();
    
    if (DISPLAY_ALL) msg_string += ", port: " + m.getAddress();;
    
    int iTotalArg = m.getNumArgs();
    int i = -1;
    
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += "NAME: " + m.getArgAsString(i);
    if (++i < iTotalArg)                msg_string += ", STATUS: " + m.getArgAsString(i);
    if (++i < iTotalArg)                msg_string += ", FILE: " + m.getArgAsString(i);
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += ", POSITION: " + ofToString(m.getArgAsInt(i));
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += ", DURATION: " + ofToString(m.getArgAsInt(i));
    if (++i < iTotalArg)                msg_string += ", LOOPING: " + ofToString(m.getArgAsInt(i));
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += ", VOLUME: " + ofToString(m.getArgAsInt(i));
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += ", MUTE: " + m.getArgAsString(i);
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += ", ZOOM: " + ofToString(m.getArgAsInt(i));
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += ", BLUR: " + ofToString(m.getArgAsInt(i));
    
#if USE_GUI
    // add to the list of strings to display
    msg_strings[current_msg_string] = msg_string;
    timers[current_msg_string] = ofGetElapsedTimef() + 10.0f;
    current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
    // clear the next line
    msg_strings[current_msg_string] = "";
#endif
    std:: cout << msg_string << "\n";
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
    y += 30;
    
    
#if USE_GUI
    string osc_buf;
    buf = "listening for osc messages on port" + ofToString(m_iReceivePort);
    //ofDrawBitmapString(osc_buf, 10, 20);
    ofDrawBitmapString(osc_buf, x, y);
    y += 20;
    
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        ofDrawBitmapString(msg_strings[i], x, y + 15 * i);
    }
#endif
}

#if MAC_PLAYS_AUDIO
void ofApp::playWithAudioThenStop(string strFileNumber){
    ofxOscMessage m1, m2, m3, m4;
    soundPlayer.load("/Users/nicolai/Downloads/RPI/nexus/sansAudio/audio/audio" + strFileNumber + ".wav");
    soundPlayer.play();
    
    m1.setAddress("/play");
    m2.setAddress("/play");
    m3.setAddress("/play");
    m4.setAddress("/play");
    m1.addStringArg(folder_path1+"video" + strFileNumber + ".mp4");
    m2.addStringArg(folder_path2+"video" + strFileNumber + ".mp4");
    m3.addStringArg(folder_path3+"video" + strFileNumber + ".mp4");
    m4.addStringArg(folder_path4+"video" + strFileNumber + ".mp4");
    sender1video.sendMessage(m1, false);
    sender2.sendMessage(m2, false);
    sender3.sendMessage(m3, false);
    sender4.sendMessage(m4, false);
    while(soundPlayer.isPlaying()){
        ofSleepMillis(50);
    }
    m1.clear();
    m1.setAddress("/stop");
    sender1video.sendMessage(m1, false);
    sender2.sendMessage(m1, false);
    sender3.sendMessage(m1, false);
    sender4.sendMessage(m1, false);
    
}
#endif


void ofApp::boilerplate(){
    //main folder paths. Pressing 'p' or 'l' will play or loop all media files in these folders
    folder_path1 = "/media/pi/usb1/";
    folder_path2 = "/media/pi/usb2/";
    folder_path3 = "/media/pi/usb3/";
    folder_path4 = "/media/pi/usb4/";
    
    // open outgoing connections
    sender1video.setup(pi1_ip, iPiVideoPort);
    sender2.setup(pi2_ip, iPiVideoPort);
    sender3.setup(pi3_ip, iPiVideoPort);
    sender4.setup(pi4_ip, iPiVideoPort);
    
    //osc receiver stuff
    m_iReceivePort = 9999;
    cout << "listening for osc messages on port " << m_iReceivePort << "\n";
    receiver.setup(m_iReceivePort);
    current_msg_string = 0;
    
    //set up various gui elements
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


