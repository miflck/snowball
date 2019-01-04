//
//  DataManager.cpp
//  snowball
//
//  Created by Flückiger Michael on 10.12.18.
//




#include "DataManager.hpp"


ofEvent<ofVec3f> DataManager::maxPeak = ofEvent<ofVec3f>();


DataManager::DataManager(){
}
//--------------------------------------------------------------

DataManager::~DataManager(){
    
}

void DataManager::update(){
    
    if(floatValues.size()>2){
        float f1=floatValues[0];
        float f2=floatValues[floor(floatValues.size()/2)];
        float f3=floatValues[floatValues.size()-1];
        
        if(f2>f1 && f2 > f3 && f2-f1>100){
            cout<<"max peak"<<endl;

        }
        
        if(f2<f1 && f2 < f3 && f1-f2>100){
            cout<<"min peak"<<endl;
        }
        
    }
    
    
    if(zValues.size()>2){
        float f1=zValues[0];
        float f2=zValues[floor(zValues.size()/2)];
        float f3=zValues[zValues.size()-1];
        
        
        if(f2>f1 && f2 > f3 && f2-f1>peakDiff){
            cout<<"-----------max peak------------"<<endl;
            cout<<f1<<" "<<f2<<" "<<f3<<endl;
            ofVec3f v =ofVec3f(f1,f2,f3);
            ofNotifyEvent(maxPeak,v );
        }
        
        if(f2<f1 && f2 < f3 && f1-f2>peakDiff){
           // cout<<"min peak"<<endl;
           // cout<<f1<<" "<<f2<<" "<<f3<<endl;
            ofVec3f v =ofVec3f(f1,f2,f3);
          //  ofNotifyEvent(maxPeak,v );
        }
        
        
    }
    
    
    
    if(zValues.size()>2){
        float f1=zValues[0];
        float f2=getzAverage();
        float f3=zValues[zValues.size()-1];

        float lf=ofLerp(f1, f3, 0.8);
        
       // cout<<"avg "<<f2<<" "<<f2-f3<<" "<<lf<<" "<<lf-f2<<endl;
        
    }
    
    
    
}

void DataManager::draw(){
    
    
}


float DataManager::getFloatAverage(){
    float f;
    for(int i=0;i<floatValues.size();i++){
        f+=floatValues[i];
    }
    f/=floatValues.size();
    return f;
}





void DataManager::addFloatValue(float d){
    floatValues.push_back(d);
    
    if(floatValues.size()>maxFloatValues){
        floatValues.erase(floatValues.begin());
    }
    // cout<<floatValues.size()<<endl;
}


float DataManager::getxAverage(){
    float f;
    for(int i=0;i<xValues.size();i++){
        f+=xValues[i];
    }
    f/=xValues.size();
    return f;
}

float DataManager::getyAverage(){
    float f;
    for(int i=0;i<yValues.size();i++){
        f+=yValues[i];
    }
    f/=yValues.size();
    return f;
}

float DataManager::getzAverage(){
    float f;
    for(int i=0;i<zValues.size();i++){
        f+=zValues[i];
    }
    f/=zValues.size();
    return f;
}


void DataManager::addxValue(float d){
    xValues.push_back(d);
    if(xValues.size()>maxFloatValues){
       xValues.erase(xValues.begin());
    }
}

void DataManager::addyValue(float d){
    yValues.push_back(d);
    if(yValues.size()>maxFloatValues){
        yValues.erase(yValues.begin());
    }
}

void DataManager::addzValue(float d){
    zValues.push_back(d);
    if(zValues.size()>maxFloatValues){
        zValues.erase(zValues.begin());
    }
}

ofVec3f DataManager::getLatestValues(){
    return ofVec3f(xValues.back(),yValues.back(),zValues.back());
}

ofVec3f DataManager::getLatestMaximals(){
    float x1=xValues[0];
    float x2=xValues[floor(xValues.size()/2)];

    float y1=yValues[0];
    float y2=yValues[floor(yValues.size()/2)];
    
    float z1=zValues[0];
    float z2=zValues[floor(zValues.size()/2)];
    
    return ofVec3f(x2-x1,y2-y1,z2-z1);
}


