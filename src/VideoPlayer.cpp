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
    
   // cout<<"state "<<state<<endl;
    
    //bool isLoaded=true;
    
   // if(introClip->isFrameNew()){
      //  introClip->update();//}
   // if(idleClip->isFrameNew()){
      //  idleClip->update();//}
    
    
    
    // if(introClip->getIsMovieDone() && introClip->isPlaying()){
    if(state == INTRO && introClip->getIsMovieDone()){
        
        // ofSendMessage("intro CLIP is done");
        // introClip->setPosition(0);
        //cout<<"intro is done"<<endl;
        setState(IDLE);
    }
    

    
    switch (state) {
     case INTRO:
            if(introClip->isLoaded()&!introClip->isPlaying()){
                introClip->play();
            }

     if(introClip->isLoaded()){
         introClip->update();
         if(getDuration()-(getDuration()*getPosition())<3 &! loopsound.isPlaying()){
             startLoopsound();
         }
      //   cout<<getDuration()<<" "<<getPosition()<<" seconds "<<(getDuration()*getPosition())<<endl;
     }
     break;
     
     case IDLE:
     if(idleClip->isLoaded()){
     idleClip->update();
     
     }
     
     break;
     
     default:
     break;
     }

    
    
    
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
    

    
  /*  if(idleClip->getIsMovieDone()){
        // ofSendMessage("idle CLIP is done");
    }*/
  
    
}
//--------------------------------------------------------------



void VideoPlayer::startLoopsound(){
    cout<<"++++++++++++++++++++++++++ start Loopsound++++++++++++++"<<endl;
    loopsound.setLoop(true);
    loopsound.play();
    
}

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
    // introClip->setPixelFormat(OF_PIXELS_NATIVE);

    //introClip->loadAsync(p);
    //cout<<"loading intro"<<p<<endl;
    introClipPath=p;
    //introClip->setLoopState(OF_LOOP_NONE);
}

void VideoPlayer::setIdleClip(string p){
   // idleClip->setPixelFormat(OF_PIXELS_NATIVE);

  //  idleClip->loadAsync(p);
    idleClipPath=p;
   // cout<<"loading idle "<<p<<endl;

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
                
                //stopAndResetIdle();
               // idleClip->setFrame(0);
                introClip->play();
            }
            break;
            
        case IDLE:
            if(idleClip->isLoaded()){
              //  stopAndResetIntro();
             //  introClip->setPaused(true);
             //  idleClip->firstFrame();
             //   idleClip->stop();

//                idleClip->setFrame(0);

               /* if(!isThreadRunning()){
                    startThread(introClip);
                }*/
               // introClip->setFrame(0);
                
                
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
//    introClip->stop();
//    introClip->setPosition(0);
    
    video=introClip;
  //  if(!isThreadRunning())startThread();
    
}
void VideoPlayer::stopAndResetIdle(){
   /* idleClip->stop();
    idleClip->setPosition(0);
    */
    video=idleClip;
   // if(!isThreadRunning())startThread();
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

   /* lock();
    video->setPaused(true);
    video->setFrame(0);
    unlock();
    
    stopThread();
*/
    
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



void VideoPlayer::setSoundpath(string s){
    soundpath=s;
}

void VideoPlayer::loadSound(){
    loopsound.load(soundpath);
   //9 loopsound.play();
    //loopsound.setVolume(0.75f);

}

void VideoPlayer::loadVideos(){
    introClip->loadAsync(introClipPath);
    idleClip->loadAsync(idleClipPath);
    idleClip->setLoopState(OF_LOOP_NORMAL);
    loadSound();
}
void VideoPlayer::closeVideos(){
    cout<<"---------------close---------"<<endl;
    introClip->setPaused(true);
    introClip->close();
    idleClip->setPaused(true);
    idleClip->close();
    loopsound.stop();
    loopsound.unload();
}
