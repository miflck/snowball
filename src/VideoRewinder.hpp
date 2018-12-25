//
//  Video.hpp
//  snowball
//
//  Created by Flückiger Michael on 29.11.18.
//

#ifndef VideoRewinder_hpp
#define VideoRewinder_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Video.hpp"

class VideoRewinder:  public ofThread{
    
public:
    
    VideoRewinder();
    virtual ~VideoRewinder();
    
   // void setLoopstate(string _loopstate);
   // string getLoopstate();

    void threadedFunction();
    shared_ptr<Video> video;
    
    void setVideoPointer(shared_ptr<Video> _video);
    void start();
    void stop();
    
private:
 //   string loopstate="";
};
#endif /* Video_hpp */
