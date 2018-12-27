//
//  VideoPlayer.hpp
//  snowball
//
//  Created by Flückiger Michael on 29.11.18.
//

#ifndef VideoPlayer_hpp
#define VideoPlayer_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Video.hpp"
#include "VideoRewinder.hpp"


#define INIT 000
#define INTRO 100
#define IDLE 200

class VideoPlayer: public ofBaseApp{

public:
VideoPlayer();
virtual ~VideoPlayer();

void setup();
void update();
void draw();

void setState(int state);
int getState();

bool getIsVideoLoaded();

void forward();
void stop();
    void start();
void showVideo(bool _showVideo);

    void setIntroClip(string p);
    void setIdleClip(string p);
    
    
    void stopAndReset();
    
    void stopAndResetIdle();
    void stopAndResetIntro();

    ofImage *img;
    
    void threadedFunction();

    
    float getDuration();
    float getPosition();
    
    
    void loadIntroclip();
    void loadIdleclip();
    string getIntroPath();
    string getIdlePath();
    
    VideoRewinder rewinder;
    
private:
    //shared_ptr<Video> movieclip;
    //vector<Video> videos;
    //vector<shared_ptr<Video> > videos;
    
    shared_ptr<Video> introClip;
    shared_ptr<Video> idleClip;
    shared_ptr<Video> video;


    bool rewind;
    
    int state;
    
    
    bool bIsVideoLoaded;
    bool bShowVideo=false;
    
    string introclipPath;
    string idleclipPath;

};
#endif /* VideoPlayer_hpp */
