#pragma once

#include "ofMain.h"
#include "VideoPlayer.hpp"

#include "MovingObject.hpp"
#include "ofxJsonSettings.h"


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
    
    MovingObject o;

    void next();
    void debugNext();

private:
    int videoIndex=0;
    
    ofImage mask;
    
    vector <ofImage > images;

    ofVec2f *boundingBoxPosition;
    ofVec2f *boundingBoxDimension;

		
};
