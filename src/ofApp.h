#pragma once

#include "ofMain.h"
#include "VideoPlayer.hpp"

#include "MovingObject.hpp"
#include "ofxJsonSettings.h"
#include "ofxSimpleSerial.h"
#include "DataManager.hpp"
#include "ofxDatGui.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
        vector<shared_ptr<VideoPlayer> > videos;
      //  shared_ptr<VideoPlayer> video;
    
    vector <MovingObject> particles;
    
    void next();
    void debugNext();
    
    void shake();

    
    
    bool debug=true;
    
    bool bShowMask=true;
    
    ofxDatGuiSlider* minslider;
    ofxDatGuiSlider* maxslider;

    void onSliderEvent(ofxDatGuiSliderEvent e);
    bool bShowGui=false;
    
private:
    int videoIndex=0;
    
    ofImage mask;
    
    vector <ofImage > images;

    ofVec2f *boundingBoxPosition;
    ofVec2f *boundingBoxDimension;

    
    bool bUseSerial=false;
    ofxSimpleSerial    serial;
    void        onNewMessage(string & message);
    string        message;
    bool        requestRead;
    
    DataManager datamanager;
    
    float imageFadeDuration=10;
		
};
