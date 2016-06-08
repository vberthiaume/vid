#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 9500
#define NUM_MSG_STRINGS 20

#ifndef USE_GUI
#define USE_GUI 0
#endif

class ofApp : public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void printMsgs(ofxOscMessage &m);
    
    ofTrueTypeFont font;
    ofxOscReceiver receiver;
    
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    
    int mouseX, mouseY;
    string mouseButtonState;
    
    ofImage receivedImage;
    
    ofSoundPlayer soundPlayers[6];
    
    bool m_bIsPlaying;
    bool m_bIsLooping;
    bool m_bPlayerDone[6]{false};
    bool m_bPlayerStarted[6]{false};
};
