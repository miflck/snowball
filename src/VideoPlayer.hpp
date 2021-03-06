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


#define INIT 000
#define INTRO 100
#define IDLE 200

class VideoPlayer: public ofBaseApp, ofThread{

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
    
    string introClipPath;
    string idleClipPath;
    void stopAndReset();
    
    void stopAndResetIdle();
    void stopAndResetIntro();

    ofImage *img;
    
    void threadedFunction();

    
    float getDuration();
    float getPosition();
    
    void loadVideos();
    void closeVideos();
    
    shared_ptr<Video> introClip;
    shared_ptr<Video> idleClip;
    shared_ptr<Video> video;
    
    
    ofSoundPlayer  loopsound;
    string soundpath;
    void setSoundpath(string s);
    void loadSound();
    void startLoopsound();
    


    static ofEvent<bool> readyToPlay;
    bool notified=false;
    static ofEvent<bool> timeOut;


private:

    bool rewind;
    int state;
    bool bIsVideoLoaded;
    bool bShowVideo=false;
    
    float loopInitTime;
    float loopMaxDuration=1000*60;//*3;
    bool bTimeOut=false;

    
    
    
};
#endif /* VideoPlayer_hpp */
