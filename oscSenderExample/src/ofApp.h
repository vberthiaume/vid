#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxDatGui.h"
#include "ofAppRunner.h"

#define NUM_MSG_STRINGS 20

// OPTION 2
#ifndef OSC_SENDER_PLAYS_AUDIO
#define OSC_SENDER_PLAYS_AUDIO 1
#endif


//this is to print osc messages in main gui window
#ifndef USE_GUI
#define USE_GUI 1
#endif


//--------------------------------------------------------
class ofApp : public ofBaseApp {
    void boilerplate();
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    void sendMessageToAll(ofxOscMessage m);
    
    void playAllVideos();
    void playWithAudioThenStop(string i);
    
    ofTrueTypeFont font;
    ofxOscSender sender1, sender2, sender3, sender4;
    ofBuffer imgAsBuffer;
    ofImage img;
    ofSoundPlayer soundPlayer;
    
    ofxDatGuiTextInput* filesToPlayTextInput;
    void onTextInputEvent(ofxDatGuiTextInputEvent e);
    void onButtonEvent(ofxDatGuiButtonEvent e);
    
    ofxDatGuiButton* playButton, *loopButton;
    
    string pi1_ip, pi2_ip, pi3_ip, pi4_ip;
    string folder_path1, folder_path2, folder_path3, folder_path4;
    int iPiVideoPort = 9000;
    
    int m_iReceivePort;
    
    vector<string> playList;
    
    ofxOscReceiver receiver;
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    void printMsgs    (ofxOscMessage &m);
    
    bool m_bLooping = false;
#if OSC_SENDER_PLAYS_AUDIO
    bool m_bStartedSoundPlayer = false;
    bool m_bSoundPlayerIsPlaying = false;
#endif
    
    string m_sMacAudioPath;
};

