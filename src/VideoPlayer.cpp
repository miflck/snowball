//
//  VideoPlayer.cpp
//  snowball
//
//  Created by Flückiger Michael on 29.11.18.
//

#include "VideoPlayer.hpp"

VideoPlayer::VideoPlayer(){
    
    shared_ptr<Video> a(new Video);
    introClip=a;
    shared_ptr<Video> b(new Video);
    idleClip=b;

    bShowVideo=true;
}
//--------------------------------------------------------------

VideoPlayer::~VideoPlayer(){
    
}
//--------------------------------------------------------------

void VideoPlayer::setup(){

 //   setState(IDLE);
}
//--------------------------------------------------------------

void VideoPlayer::update(){
    //bool isLoaded=true;
    switch (state) {
        case INTRO:
            if(introClip->isLoaded()){
            introClip->update();
            }
            break;
            
        case IDLE:
            if(idleClip->isLoaded()){
                idleClip->update();
                if(idleClip->getIsMovieDone()){
                    ofSendMessage("idle CLIP is done");
                }
            }
            
            break;
 
        default:
            break;
    }
    
    
    if(introClip->getIsMovieDone()){
        ofSendMessage("intro CLIP is done");
        introClip->setPosition(0);
        setState(IDLE);
    }
    

    
    
}
//--------------------------------------------------------------


void VideoPlayer::draw(){
    if(bShowVideo){
        switch (state) {
            
            case INTRO:
                if(introClip->isLoaded()){
                    introClip->draw(0,0);
                }
                break;
                
            case IDLE:
                if(idleClip->isLoaded()){
                    idleClip->draw(0,0);
                }
                break;
                
            default:
                break;
        }
    }
}


void VideoPlayer::setIntroClip(string p){
    introClip->load(p);
    cout<<"loading intro"<<p<<endl;
    introClip->setLoopState(OF_LOOP_NONE);
    
}

void VideoPlayer::setIdleClip(string p){
    idleClip->load(p);
    cout<<"loading idle "<<p<<endl;

}

void VideoPlayer::setState(int _state){
    state=_state;
    switch (state) {
        case INTRO:
            if(introClip->isLoaded()){
                stopAndResetIdle();
                introClip->play();
            }
            break;
            
        case IDLE:
            if(idleClip->isLoaded()){
                stopAndResetIntro();
                idleClip->play();
            }
            break;
            
        default:
            break;
    }
}

int VideoPlayer::getState(){
    return state;
}

bool VideoPlayer::getIsVideoLoaded(){
    return bIsVideoLoaded;
}


void VideoPlayer::start(){
    introClip->play();
}

void VideoPlayer::stop(){
   // actualmovieclip->stop();
}

void VideoPlayer::stopAndResetIntro(){
    introClip->stop();
    introClip->setPosition(0);
}
void VideoPlayer::stopAndResetIdle(){
    idleClip->stop();
    idleClip->setPosition(0);
}

void VideoPlayer::stopAndReset(){
    setState(INIT);
    stopAndResetIntro();
    stopAndResetIdle();
}


void VideoPlayer::showVideo(bool _showVideo){
    bShowVideo=_showVideo;
    cout<<"show video "<<_showVideo<<bShowVideo<<endl;
}
