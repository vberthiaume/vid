#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxDatGui.h"

//--------------------------------------------------------
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
    
    void sendMessageToAll(ofxOscMessage m);
    void playAllVideos();
    void setVolumeToMax();
    
    ofTrueTypeFont font;
    ofxOscSender sender1, sender2, sender3, sender4, senderLocal;
    ofBuffer imgAsBuffer;
    ofImage img;
    ofSoundPlayer soundPlayer;
    
    ofxDatGuiTextInput* filesToPlayTextInput;
    void onTextInputEvent(ofxDatGuiTextInputEvent e);
    void onButtonEvent(ofxDatGuiButtonEvent e);
    
    ofxDatGuiButton* playButton, *loopButton;
    
    string pi1_ip, pi2_ip, pi3_ip, pi4_ip, local_ip;
    string folder_path1, folder_path2, folder_path3, folder_path4;
    int iPiPort;
    
    vector<string> playList;
};

