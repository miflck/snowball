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
    
    shared_ptr<Video> c(new Video);
    video=a;

    bShowVideo=true;
    rewind=false;
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
  //  if(introClip->isFrameNew()){
        introClip->update();
   // }
   // if(idleClip->isFrameNew()){
    idleClip->update();
   // }

    
   /* switch (state) {
        case INTRO:
            if(introClip->isLoaded()){
            introClip->update();
            }
            break;
            
        case IDLE:
            if(idleClip->isLoaded()){
                idleClip->update();
              
            }
            
            break;
 
        default:
            break;
    }*/
    
    
   // if(introClip->getIsMovieDone() && introClip->isPlaying()){
        if(introClip->getIsMovieDone()){

       // ofSendMessage("intro CLIP is done");
       // introClip->setPosition(0);
        cout<<"intro is done"<<endl;
        setState(IDLE);
    }
    
  /*  if(idleClip->getIsMovieDone()){
        // ofSendMessage("idle CLIP is done");
    }*/
  
    
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
  //  introClip->loadAsync(p);
    introclipPath=p;
    cout<<"loading intro"<<p<<endl;
    introClip->setLoopState(OF_LOOP_NONE);
}

string VideoPlayer::getIntroPath(){
    return introclipPath;
}

void VideoPlayer::setIdleClip(string p){
  //  idleClip->loadAsync(p);
    idleclipPath=p;
    cout<<"loading idle "<<p<<endl;

}
string VideoPlayer::getIdlePath(){
    return idleclipPath;
}


void VideoPlayer::loadIntroclip(){
    cout<<"************ load intro "<<introclipPath<<" *********"<<endl;
    introClip->loadAsync(introclipPath);
    introClip->setLoopState(OF_LOOP_NONE);

}

void VideoPlayer::loadIdleclip(){
    cout<<"************ load idle "<<idleclipPath<<" *********"<<endl;
    idleClip->loadAsync(idleclipPath);
}

void VideoPlayer::setState(int _state){
    state=_state;
    cout<<"switch "<<state<<endl;
    switch (state) {
        case INTRO:
            if(introClip->isLoaded()){
               // idleClip->setPaused(true);
              // introClip->firstFrame();
                //introClip->setFrame(0);
             
               /* if(!isThreadRunning()){
                    startThread(idleClip);
                }*/
                
                stopAndResetIdle();
               // idleClip->setFrame(0);
                if(introClip->isFrameNew()){
                    introClip->play();
                }
            }
            break;
            
        case IDLE:
            if(idleClip->isLoaded()){
                stopAndResetIntro();
             //  introClip->setPaused(true);
             //  idleClip->firstFrame();
             //   idleClip->stop();

//                idleClip->setFrame(0);

               /* if(!isThreadRunning()){
                    startThread(introClip);
                }*/
               // introClip->setFrame(0);
                
                if(idleClip->isFrameNew()){
                    idleClip->play();
                }
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
//    introClip->stop();
//    introClip->setPosition(0);
    
    video=introClip;
   // startThread();
    
    rewinder.setVideoPointer(introClip);
    
}
void VideoPlayer::stopAndResetIdle(){
   /* idleClip->stop();
    idleClip->setPosition(0);
    */
    video=idleClip;
    //startThread();
    
    rewinder.setVideoPointer(idleClip);

}

void VideoPlayer::stopAndReset(){
    setState(INIT);
    stopAndResetIntro();
   // stopAndResetIdle();
}


void VideoPlayer::showVideo(bool _showVideo){
    bShowVideo=_showVideo;
    cout<<"show video "<<_showVideo<<bShowVideo<<endl;
}


void VideoPlayer::threadedFunction(){

 /*   lock();
    video->setPaused(true);
    video->setFrame(0);
    unlock();
    */
 //   stopThread();

    
}

float VideoPlayer::getDuration(){
    if(getState()==IDLE){
        return idleClip->getDuration();
    }else if(getState()==INTRO){
        return introClip->getDuration();

    }
    
}

float VideoPlayer::getPosition(){
    if(getState()==IDLE){
        return  idleClip->getPosition();
        
    }else if(getState()==INTRO){
        return  introClip->getPosition();

    }
    
    
}
