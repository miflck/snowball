//
//  Video.cpp
//  snowball
//
//  Created by Flückiger Michael on 29.11.18.
//

#include "VideoRewinder.hpp"

VideoRewinder::VideoRewinder(){
   // startThread();
    cout<<"init rewinder"<<endl;

}
//--------------------------------------------------------------

VideoRewinder::~VideoRewinder(){
   // stopThread();
    cout<<"stopThread"<<endl;
}


void VideoRewinder::setVideoPointer(shared_ptr<Video> _video){
    video=_video;
    if(!isThreadRunning())startThread();
   // startThread();
}

void VideoRewinder::start(){
    startThread();
}

void VideoRewinder::stop(){
    stopThread();
}


void VideoRewinder::threadedFunction(){
    while(isThreadRunning())
    {
        // Attempt to lock the mutex.  If blocking is turned on,
        if(lock())
        {
            // if(video->getPosition()!=0){
                 video->setPaused(true);
                // video->setFrame(0);
             //}
            unlock();

        }
        
        if(video->getPosition()==0){
          //  stopThread();
        }
    }
}


//--------------------------------------------------------------

