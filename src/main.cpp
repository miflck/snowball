#include "ofMain.h"
#include "ofApp.h"
#include "ofxWatchdog.h"


//========================================================================
int main( ){
      //  ofxWatchdog::watch(2000, true, true, true);
    ofxWatchdog::boot(2000, true, true, true);

	//ofSetupOpenGL(1920,1080,OF_WINDOW);			// <-------- setup the GL context
//   ofSetupOpenGL(1920,1080,OF_WINDOW);            // <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp(new ofApp());
    
    
    
  ofGLFWWindowSettings settings;
   // settings.setGLVersion(3, 2);
    settings.multiMonitorFullScreen = true;
   // settings.windowMode = OF_FULLSCREEN;
    settings.width = 1920*2;
    settings.height = 1080;
    ofCreateWindow(settings);
    
    ofxWatchdog::trap();

    ofRunApp(new ofApp());

    
    
   /* ofGLESWindowSettings settings;
    settings.setGLESVersion(2);
    settings.width = 1920;
    settings.height = 1080;
    ofCreateWindow(settings);
    ofRunApp(new ofApp);*/
}
