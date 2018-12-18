//
//  DataManager.hpp
//  snowball
//
//  Created by Flückiger Michael on 10.12.18.
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include <stdio.h>
#include "ofMain.h"

class DataManager {
    
public:
    
    DataManager();
    virtual ~DataManager();
    
    void update();
    void draw();
    void addFloatValue(float d);
    
    // void setLoopstate(string _loopstate);
    // string getLoopstate();
    
    
    float getFloatAverage();
    
private:
    //   string loopstate="";
    

    vector<float> floatValues;
    int maxFloatValues=10;
    
};
#endif /* DataManager_hpp */
