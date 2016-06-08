#include "ofMain.h"
#include "ofApp.h"
#if USE_GUI
#else
#include "ofAppNoWindow.h"
#endif
//========================================================================
int main( ){

#if USE_GUI
	ofSetupOpenGL(640,480, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());
#else
//    ofApp * app = new ofApp();
//    app->setup();
//    while(1){
//        app->update();
//    }
    
    ofAppNoWindow window;
    ofSetupOpenGL(&window,640,480,OF_WINDOW);
    ofRunApp(new ofApp);
#endif
    

}
