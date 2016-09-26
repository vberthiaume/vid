#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxDatGui.h"
#include "ofAppRunner.h"

#define NUM_MSG_STRINGS 20

#define NUM_RPIS 4

// OPTION 2
#ifndef OSC_SENDER_PLAYS_AUDIO
#define OSC_SENDER_PLAYS_AUDIO 1
#endif

//--------------------------------------------------------
class ofApp : public ofBaseApp {
    void boilerplate();
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    ofxOscSender sender1, sender2, sender3, sender4;
    void sendMessageToAll(ofxOscMessage m);
    void resendMessagesToAll();
    
    void playAllVideos();
    void playWithAudio(string i);
    
    string pi1_ip, pi2_ip, pi3_ip, pi4_ip;
    string folder_path1, folder_path2, folder_path3, folder_path4;
    int iPiVideoPort = 9000;
    
    
    vector<string> playList;
    int m_iCurPlaylistItem = 0;
    bool m_bLooping = false;

    
    //GUI THINGS
    ofBuffer imgAsBuffer;
    ofImage img;
    ofxDatGuiTextInput* filesToPlayTextInput;
    void onTextInputEvent(ofxDatGuiTextInputEvent e);
    void onButtonEvent(ofxDatGuiButtonEvent e);
    ofxDatGuiButton* playButton, *loopButton, *toggleButton;
    
    //OSC RECEIVER THINGS
    int m_iReceivePort;
    ofxOscReceiver receiver;
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    void logMsg(string msg_string);
    
#if OSC_SENDER_PLAYS_AUDIO
    ofSoundPlayer soundPlayer;
    bool m_bStartedSoundPlayer = false;
    bool m_bSoundPlayerIsPlaying = false;
    string m_sMacAudioPath;
    void soundPlayerJustStoppedPlaying();
#endif
    
    //OSC MESSAGES CONFIRMATION
    bool m_bOscConfirmations[NUM_RPIS];
    void confirmMessage(ofxOscMessage m);
    string getMsgContent(ofxOscMessage m);
    bool m_bNeedOscConf = false;
    void resetOscConfs(){
        for (int i=0; i<NUM_RPIS; ++i){
            m_bOscConfirmations[i] = false;
        }
    }
    long m_lUpdateCtr = 0;
    ofxOscMessage m_oLastOscMsgSent[NUM_RPIS];
    string m_sRpiStatuses[NUM_RPIS];
};

