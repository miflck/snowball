//
//  DataManager.cpp
//  snowball
//
//  Created by Flückiger Michael on 10.12.18.
//

#include "DataManager.hpp"
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
        
        if(f2>f1 && f2 > f3){
            cout<<"max peak"<<endl;
        }
        
        if(f2<f1 && f2 < f3){
            cout<<"min peak"<<endl;
        }
        
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
