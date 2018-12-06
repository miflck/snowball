#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){
    
    Settings::get().load("data.json");


    mask.load("mask_old.png");
    
    boundingBoxPosition=&Settings::getVec2("boundingBoxPosition");
    boundingBoxDimension=&Settings::getVec2("boundingBoxDimension");

    
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
                string ext = ofFilePath::getFileExt(s);

                // load movies
                if(ext=="mov"){
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
                }
               // load image
                if(ext=="png"){
                    ofImage img;
                    img.load(ofFilePath::getAbsolutePath(newDir.getPath(i)));
                    cout<<"load "<<ofFilePath::getAbsolutePath(newDir.getPath(i))<<endl;
                    images.push_back(img);
                    vp->img=&img;
                }
               
            }
            vp->setState(INIT);
            videos.push_back(vp);

        }
    }
    //Debug
   /* if(videos.size()>0){
        video=videos[videoIndex];
    }
    video->setState(INTRO);*/
   // video->start();
    
    
    videos[0]->setState(INTRO);

    
    for(int i=0;i<1000;i++){
        MovingObject o;
        o.setImage(&images[0]);
        o.setNewImage(&images[0],ofRandom(2));

        o.setup();
        o.setPosition(ofGetWidth()/2, ofGetHeight()/2);
        o.setMaxSpeed(ofRandom(10,20));
        o.bSeekTarget=false;
        o.setSeekForce(0);
        //o.setSpeed(1,1);
        //o.setWanderForce(1);
        o.setGravity(true);
        o.setGravityForce(ofVec2f(0,00.02));
        o.addForce(ofVec2f(ofRandom(-1,1)*10,ofRandom(0.5,-1)*10),ofRandom(20,50));
        o.setBoundingBox(ofRectangle(*boundingBoxPosition,boundingBoxDimension->x,boundingBoxDimension->y));
        particles.push_back(o);
    }
    o.setImage(&images[0]);
    o.setNewImage(&images[0],ofRandom(2));

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
    for(int i=0;i<videos.size();i++){
        videos[i]->update();
    }
  //  video->update();

    //videos[videoIndex%videos.size()]->update();
    
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
  //  video->draw();
    ofPopMatrix();
    
    for(int i=0;i<particles.size();i++){
        particles[i].draw();
      //  images[videoIndex%videos.size()].draw(particles[i].getPosition());

    }
    o.draw();
    mask.draw(0,0);
   // cout<<*boundingBoxPosition<<" "<<boundingBoxDimension->x<<endl;
   // ofDrawRectangle(*boundingBoxPosition,boundingBoxDimension->x,boundingBoxDimension->y);
}




void ofApp::next(){
   // if(video->getState()==IDLE){
        videos[videoIndex%videos.size()]->stopAndReset();
    
    
    
    
        videoIndex++;

       /*if(videos.size()>0){
            video=videos[videoIndex%videos.size()];
           video->setState(INTRO);
        }*/
    videos[videoIndex%videos.size()]->setState(INTRO);
  //  }
    
    for(int i=0;i<particles.size();i++){
        particles[i].setNewImage(&images[videoIndex%videos.size()],ofRandom(5));
    }
    
}
/*
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
*/

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key =='n'){
        next();
    }
    
    if(key =='N'){
     //   debugNext();
    }

    
    if(key=='f'){
        
        
        for(int i=0;i<particles.size();i++){
            particles[i].addForce(ofVec2f(ofRandom(-1,1)*10,ofRandom(0.5,-1)*10),ofRandom(20,50));
        }
        
        o.addForce(ofVec2f(ofRandom(-1,1)*10,ofRandom(0,-1)*10), 50);
    }
    
    
    if(key=='b'){
        //  mover.setSlowDown(true);
        boundingBoxPosition->set(ofGetMouseX(),ofGetMouseY());
        Settings::get().save("data.json");
    }
    
    
    if(key=='d'){
        boundingBoxDimension->set(ofGetMouseX()-boundingBoxPosition->x,ofGetMouseY()-boundingBoxPosition->y);
        Settings::get().save("data.json");
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
