//
//  Data.hpp
//  snowball
//
//  Created by Flückiger Michael on 10.12.18.
//

#ifndef Data_hpp
#define Data_hpp

#include <stdio.h>
#include "ofMain.h"

class Data {
    
public:
    
    Data();
    virtual ~Data();
    
    // void setLoopstate(string _loopstate);
    // string getLoopstate();
    void addFloat(float f);
    
    
private:
    
    float floatData;
    //   string loopstate="";
};

#endif /* Data_hpp */
