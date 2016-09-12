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


////////////////////////////////////////////////////////////////////////////////

void ofApp::setup(){

	ofBackground(25, 25, 25);
    ofSetFrameRate(20);
    
    //All IP addresses
//    pi1_ip = "192.168.0.101";   //NEW RPI1
//    pi1_ip = "192.168.0.105";   //OLD RPI1
    pi1_ip = "10.226.226.229";    //SCHOOL
    pi2_ip = "192.168.0.102";
    pi3_ip = "192.168.0.103";
    pi4_ip = "192.168.0.104";
    
#if OSC_SENDER_PLAYS_AUDIO
//    m_sMacAudioPath = "/Users/nicolai/Downloads/RPI/AAAoriginaux/audio/";
    m_sMacAudioPath = "/Users/nicolai/Downloads/RPI/nexus30secKeyboard/audio/";
#endif
    
    boilerplate();
}

void ofApp::keyPressed(int key){

    //play videos one shot(p) or in a loop(l)
    if(key == 'p' || key == 'P' || key == 'l' || key == 'L'){
        if(key == 'p' || key == 'P'){
            ofxOscMessage m;
            m.setAddress("/unloop");
            sendMessageToAll(m);
        } else {
            ofxOscMessage m;
            m.setAddress("/loop");
            sendMessageToAll(m);
        }
        playAllVideos();
        //        soundPlayer.play();
    }
    
    //stop playing
    if( key == 's' || key == 'S'){
        ofxOscMessage m;
        m.setAddress("/stop");
        sendMessageToAll(m);
        //        soundPlayer.stop();
    }

#warning next and back may return previous file name as playing
    //play next video
    if( key == 'n' || key == 'N'){
        ofxOscMessage m;
        m.setAddress("/next");
        sendMessageToAll(m);
    }
    //play previous video
    if( key == 'b' || key == 'B'){
        ofxOscMessage m;
        m.setAddress("/prev");
        sendMessageToAll(m);
    }
    //toggle info screen
    if(key == 'i' || key == 'I'){
        ofxOscMessage m;
        m.setAddress("/info");
        sendMessageToAll(m);
//        sendAndConfirmMessageToAll(m);
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
    if(key == 'c'){
        for(int i = 0; i < NUM_MSG_STRINGS; i++){
            msg_strings[i] = "";
        }
        current_msg_string = 0;
    }
}

void ofApp::playAllVideos(){
        ofxOscMessage m1, m2, m3, m4;
        m1.setAddress("/play");
        m1.addStringArg(folder_path1);
        sender1.sendMessage(m1, false);
        m2.setAddress("/play");
        m2.addStringArg(folder_path2);
        sender2.sendMessage(m2, false);
        m3.setAddress("/play");
        m3.addStringArg(folder_path3);
        sender3.sendMessage(m3, false);
        m4.setAddress("/play");
        m4.addStringArg(folder_path4);
        sender4.sendMessage(m4, false);
}

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void ofApp::confirmMessage(ofxOscMessage m){
    string sIp = m.getRemoteIp();
    if (hasEnding(sIp, pi1_ip)){
        m_bOscConfirmations[0] = true;
        ++m_iOscAllConfirmed;
        cout << "confirm RPI1\n";
    }
    else if (hasEnding(sIp, pi2_ip)){
        m_bOscConfirmations[1] = true;
        ++m_iOscAllConfirmed;
        cout << "confirm RPI2\n";
    }
    else if (hasEnding(sIp, pi3_ip)){
        m_bOscConfirmations[2] = true;
        ++m_iOscAllConfirmed;
        cout << "confirm RPI3\n";
    }
    else if (hasEnding(sIp, pi4_ip)){
        m_bOscConfirmations[3] = true;
        ++m_iOscAllConfirmed;
        cout << "confirm RPI4\n";
    }    
}

//--------------------------------------------------------------
void ofApp::update(){
    //update gui stuff
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
        ofxOscMessage m;
        receiver.getNextMessage(m);
        confirmMessage(m);
        printMsgs(m);
    }
    
    if (m_bNeedOscConf){
        if (++m_lUpdateCtr % 1000 == 0){
            if (m_iOscAllConfirmed < NUM_RPIS){
                sendMessageToAll(m_oLastOscMsgSent);
            } else {
                m_iOscAllConfirmed = 0;
                resetOscConfs();
            }
        }
    } else {
        m_lUpdateCtr = 0;
    }
    
    
#if OSC_SENDER_PLAYS_AUDIO
    if (m_bStartedSoundPlayer){
        if (soundPlayer.isPlaying()){
            m_bSoundPlayerIsPlaying = true;
        } else {
            ofxOscMessage mStop;
            mStop.setAddress("/stop");
            sendMessageToAll(mStop);
            m_bSoundPlayerIsPlaying = false;
            m_bStartedSoundPlayer = false;
        }
    }
#endif
}

void ofApp::printMsgs(ofxOscMessage &m){
    
    
#if NEW_PRINT
    
//  IP: 10.226.226.229, STATUS: stoped, FILE: , LOOPING: 0
//  IP: 10.226.226.229, STATUS: playing, FILE: /media/pi/usb1/video1.mp4, LOOPING: 0
    
    //RPI 1: PLAY/LOOP/STOP VIDEO1
    
    //figure out which pi
    string sIp = m.getRemoteIp();
    int iCurPi;
    if (hasEnding(sIp, pi1_ip)){
        iCurPi = 0;
    } else if (hasEnding(sIp, pi2_ip)){
        iCurPi = 1;
    } else if (hasEnding(sIp, pi3_ip)){
        iCurPi = 2;
    } else if (hasEnding(sIp, pi4_ip)){
        iCurPi = 3;
    }
    
    //update corresponding status
    string sStatus = "";
    
    
    
    //print all statuses
    
    
    string sIp = m.getRemoteIp();
    
    
    
    string msg_string = "IP: ";
    int iTotalArg = m.getNumArgs(), i = -1;
    bool DISPLAY_ALL = false;
    if (DISPLAY_ALL){
        msg_string += ", port: " + m.getAddress();
    }
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += "NAME: "          + m.getArgAsString(i);
    if (++i < iTotalArg)                msg_string += ", STATUS: "      + m.getArgAsString(i);
    if (++i < iTotalArg)                msg_string += ", FILE: "        + m.getArgAsString(i);
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += ", POSITION: "    + ofToString(m.getArgAsInt(i));
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += ", DURATION: "    + ofToString(m.getArgAsInt(i));
    if (++i < iTotalArg)                msg_string += ", LOOPING: "     + ofToString(m.getArgAsInt(i));
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += ", VOLUME: "      + ofToString(m.getArgAsInt(i));
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += ", MUTE: "        + m.getArgAsString(i);
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += ", ZOOM: "        + ofToString(m.getArgAsInt(i));
    if (++i < iTotalArg && DISPLAY_ALL) msg_string += ", BLUR: "        + ofToString(m.getArgAsInt(i));
    
    // add to the list of strings to display
    msg_strings[current_msg_string] = msg_string;
    timers[current_msg_string] = ofGetElapsedTimef() + 10.0f;
    current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
    // clear the next line
    msg_strings[current_msg_string] = "";
    cout << msg_string << "\n";
    
    
#else
    
    
    string msg_string = "IP: " + m.getRemoteIp();
    int iTotalArg = m.getNumArgs(), i = -1;
    bool DISPLAY_ALL = false;
    if (DISPLAY_ALL){
        msg_string += ", port: " + m.getAddress();
    }
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
    
    // add to the list of strings to display
    msg_strings[current_msg_string] = msg_string;
    timers[current_msg_string] = ofGetElapsedTimef() + 10.0f;
    current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
    // clear the next line
    msg_strings[current_msg_string] = "";
    cout << msg_string << "\n";
#endif
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
    ofDrawBitmapString("press 'p' to play all videos one shot", x, y+=30);
    ofDrawBitmapString("press 'l' to loop all videos", x, y+=15);
    ofDrawBitmapString("press 's' to stop playing", x, y+=15);
    ofDrawBitmapString("press 'n' to play next video", x, y+=15);
    ofDrawBitmapString("press 'b' to go back to previous video", x, y+=15);
    ofDrawBitmapString("press 'i' to toggle info screen", x, y+=15);
    ofDrawBitmapString("press 'Q' to quit HPlayer", x, y+=15);
    filesToPlayTextInput->setPosition(x, y+=15);
    filesToPlayTextInput->draw();
    
    playButton->setPosition(x+300+5, y);
    loopButton->setPosition(x+300+5+75+5, y);
    playButton->draw();
    loopButton->draw();
    y += 60;
    
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        ofDrawBitmapString(msg_strings[i], x, y + 15 * i);
    }
}

#if OSC_SENDER_PLAYS_AUDIO
void ofApp::playWithAudio(string strFileNumber){
    ofxOscMessage m1, m2, m3, m4;
    soundPlayer.load(m_sMacAudioPath + "audio" + strFileNumber + ".wav");
    soundPlayer.play();

    m_bStartedSoundPlayer = true;
    
    m1.setAddress("/play");
    m2.setAddress("/play");
    m3.setAddress("/play");
    m4.setAddress("/play");
    m1.addStringArg(folder_path1+"video" + strFileNumber + ".mp4");
    m2.addStringArg(folder_path2+"video" + strFileNumber + ".mp4");
    m3.addStringArg(folder_path3+"video" + strFileNumber + ".mp4");
    m4.addStringArg(folder_path4+"video" + strFileNumber + ".mp4");
    sender1.sendMessage(m1, false);
    sender2.sendMessage(m2, false);
    sender3.sendMessage(m3, false);
    sender4.sendMessage(m4, false);
}
#endif

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e) {
    playList = split(e.text, ',');
}

//custom playlist
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e) {
    if (e.target == playButton || e.target == loopButton){
        if (playList.size() != 0){
            
            
#if OSC_SENDER_PLAYS_AUDIO
            ofxOscMessage m;
            m.setAddress("/unloop");
            sendMessageToAll(m);
            for(auto& video : playList){
                playWithAudio(video);
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
            } else {
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
            sender1.sendMessage(m1, false);
            sender2.sendMessage(m2, false);
            sender3.sendMessage(m3, false);
            sender4.sendMessage(m4, false);
#endif  //OSC_SENDER_PLAYS_AUDIO
        }
    }
}

void ofApp::sendMessageToAll(ofxOscMessage m){
    
    m_bNeedOscConf = true;
    m_oLastOscMsgSent = m;
    
    sender1.sendMessage(m, false);
    sender2.sendMessage(m, false);
    sender3.sendMessage(m, false);
    sender4.sendMessage(m, false);
}


void ofApp::boilerplate(){
    
    resetOscConfs();
    
    //main folder paths. Pressing 'p' or 'l' will play or loop all media files in these folders
    folder_path1 = "/media/pi/usb1/";
    folder_path2 = "/media/pi/usb2/";
    folder_path3 = "/media/pi/usb3/";
    folder_path4 = "/media/pi/usb4/";
    
    // open outgoing connections
    sender1.setup(pi1_ip, iPiVideoPort);
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
    
    for (int i=0; i<NUM_RPIS; ++i){
        m_sRpiStatuses[i] = "";
    }
        
}


