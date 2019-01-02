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

    void addxValue(float d);
    void addyValue(float d);
    void addzValue(float d);

    // void setLoopstate(string _loopstate);
    // string getLoopstate();
    
    
    float getFloatAverage();

    float getxAverage();
    float getyAverage();
    float getzAverage();

    ofVec3f getLatestValues();
    ofVec3f getLatestMaximals();

    
   static ofEvent<ofVec3f> maxPeak;

    
private:
    //   string loopstate="";
    

    vector<float> floatValues;
    int maxFloatValues=10;

    vector<float> xValues;
    vector<float> yValues;
    vector<float> zValues;

    
    
};
#endif /* DataManager_hpp */
