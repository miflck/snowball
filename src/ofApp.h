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
    shared_ptr<VideoPlayer> lastvideo;
     shared_ptr<VideoPlayer> thisvideo;
    shared_ptr<VideoPlayer> nextvideo;

    
    vector <MovingObject > particles;
    
    void next();
    void debugNext();
    void shake();
    void shake(ofVec3f v);


    
    
    bool debug=true;
    
    bool bShowMask=true;
    
    
    
    ofxDatGui* gui;

    ofxDatGuiSlider* minslider;
    ofxDatGuiSlider* maxslider;
    
    ofxDatGuiValuePlotter* zPlotter; 
    

    //void onSliderEvent(ofxDatGuiSliderEvent e);
    
    void onGuiSliderEvent(ofxDatGuiSliderEvent e);

    
    bool bShowGui=false;
    
    
    float scale=1;


    
    //float scale=1;
    ofxDatGuiSlider* zoom;

    bool changing=false;
    bool doChange=false;
    
    void prepareNext();

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

    float nextDebounceTimer;
    float nextDebounceDuration=500;

    
    void onMaxPeak(ofVec3f & e);
    void onReady(bool & e);
    void onTimeOut(bool & e);
    
    
    vector <ofSoundPlayer > shakesounds;
    int initShakeDebounce;
    int shakeDebounceDuration=800;
    
    float shakeEnergy;
    float shakeDamping=0.99;
    
    
    int nextThreshold=1000;
    
    bool bUseEnergy=true;
    ofxDatGuiFRM* fps;

    float imageFadeDuration=10;

    
};
