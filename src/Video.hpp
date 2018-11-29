//
//  Video.hpp
//  snowball
//
//  Created by Flückiger Michael on 29.11.18.
//

#ifndef Video_hpp
#define Video_hpp

#include <stdio.h>
#include "ofMain.h"

class Video:  public ofVideoPlayer{
    
public:
    
    Video();
    virtual ~Video();
    
   // void setLoopstate(string _loopstate);
   // string getLoopstate();

    
    
private:
 //   string loopstate="";
};
#endif /* Video_hpp */
