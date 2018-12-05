#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){
    
    string path = "movies";
    ofDirectory dir(path);
    dir.listDir();
    //go through and print out all the paths
    for(int i = 0; i < dir.size(); i++){
        if(dir.getFile(i).isDirectory()==1){
            //Video mc;
            shared_ptr<VideoPlayer> vp(new VideoPlayer);
            ofLogNotice("is dir "+dir.getPath(i));
            ofDirectory newDir(dir.getPath(i));
            newDir.listDir();
            for(int i = 0; i < newDir.size(); i++){
                ofLogNotice(newDir.getPath(i));
                string s=ofFilePath::getFileName(newDir.getPath(i));
                s=ofFilePath::removeExt(s);
                vector<string> splitName = ofSplitString( s, "_");
                
                if(splitName.back()=="1"){
                    vp->setIntroClip(ofFilePath::getAbsolutePath(newDir.getPath(i)));
                }
                
                if(splitName.back()=="2"){
                    ofLogNotice(newDir.getPath(i));

                    vp->setIdleClip(ofFilePath::getAbsolutePath(newDir.getPath(i)));
                }

                ofLogNotice("filepath "+s);

               // vector<string> splitString = ofSplitString( newDir.getPath(i), "/");
               // ofLogNotice(splitString.back());
               // vector<string> splitName = ofSplitString( newDir.getPath(i), "_");
               // ofLogNotice(splitName.back());


            }
            vp->setState(INIT);
            videos.push_back(vp);

        }
    }
    //Debug
    if(videos.size()>0){
        video=videos[videoIndex];
    }
    video->setState(INTRO);
   // video->start();
    
    
    for(int i=0;i<1000;i++){
        MovingObject o;
        o.setup();
        o.setPosition(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        o.setMaxSpeed(ofRandom(10,20));
        o.bSeekTarget=false;
        o.setSeekForce(0);
        //o.setSpeed(1,1);
        //o.setWanderForce(1);
        o.setGravity(true);
        o.setGravityForce(ofVec2f(0,00.02));
        particles.push_back(o);
    }

    o.setup();
    o.setPosition(ofGetWidth()/2, ofGetHeight()/2);
    o.setMaxSpeed(20);
    o.bSeekTarget=false;
    o.setSeekForce(0);
    //o.setSpeed(1,1);
    //o.setWanderForce(1);
    o.setGravity(true);
    o.setGravityForce(ofVec2f(0,00.05));
    //o.setTarget(ofVec2f(ofGetWidth(),ofGetHeight()));

}

//--------------------------------------------------------------
void ofApp::update(){
   /* for(int i=0;i<videos.size();i++){
        videos[i]->update();
    }*/
   // video->update();

    videos[videoIndex%videos.size()]->update();
    
    for(int i=0;i<particles.size();i++){
        particles[i].update();
    }
    o.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
   // ofScale(0.5,0.5);

      videos[videoIndex%videos.size()]->draw();
    ofPopMatrix();
    
    for(int i=0;i<particles.size();i++){
        particles[i].draw();
    }
    o.draw();
}




void ofApp::next(){
   // if(video->getState()==IDLE){
     //   videos[videoIndex%videos.size()]->stopAndReset();
        
        videoIndex++;

      //  if(videos.size()>0){
       //     video=videos[videoIndex%videos.size()];
       // }
        videos[videoIndex%videos.size()]->setState(INTRO);
  //  }
}

void ofApp::debugNext(){
    if(video->getState()==INTRO){
        video->setState(IDLE);
    }else{
        videoIndex++;
        video->stopAndReset();
        if(videos.size()>0){
            video=videos[videoIndex%videos.size()];
        }
        video->setState(INTRO);
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key =='n'){
        next();
    }
    
    if(key =='N'){
        debugNext();
    }

    
    if(key=='f'){
        
        
        for(int i=0;i<particles.size();i++){
            particles[i].addForce(ofVec2f(ofRandom(-1,1)*10,ofRandom(0.5,-1)*10),ofRandom(20,50));
        }
        
        o.addForce(ofVec2f(ofRandom(-1,1)*10,ofRandom(0,-1)*10), 50);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
