#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){
    
    shared_ptr<VideoPlayer> lastvideo(new VideoPlayer);
    shared_ptr<VideoPlayer> thisvideo(new VideoPlayer);
    shared_ptr<VideoPlayer> nextvideo(new VideoPlayer);

    ofBackground(0);
    ofSetVerticalSync(true);
    Settings::get().load("data.json");
    mask.load("mask.png");
    
    ofDisableArbTex();
    texImage.load("earth.jpg");
    ofLoadImage(mTex,"earth.jpg");
    texture=texImage.getTexture();
    
    
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
               // if(ext=="mov"){
                    if(ext=="mp4"){

                    s=ofFilePath::removeExt(s);
                    vector<string> splitName = ofSplitString( s, "_");
                    if(splitName.back()=="01"){
                        vp->setIntroClip(ofFilePath::getAbsolutePath(newDir.getPath(i)));
                    }
                    
                    if(splitName.back()=="02"){
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
                
                if(ext=="mp3"){

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
    
    
   // videos[0]->setState(INTRO);
    

    
    lastvideo=videos[videos.size()-1];
    thisvideo=videos[0];
    thisvideo->loadVideos();
    thisvideo->setState(INTRO);
    
    nextvideo=videos[1];
    nextvideo->loadVideos();
    
    nextDebounceTimer=ofGetElapsedTimeMillis();
    
    



    
    for(int i=0;i<1000;i++){
        MovingObject o;
        o.setImage(&images[0]);
        o.setNewImage(&images[0],ofRandom(2));

        o.setup();
        o.setPosition(1920/2, ofGetHeight()/2);
        o.setMaxSpeed(ofRandom(10,20));
        o.bSeekTarget=false;
        o.setSeekForce(0);
        //o.setSpeed(1,1);
        //o.setWanderForce(1);
        o.setGravity(true);
        o.setGravityForce(ofVec2f(0,00.02));
        o.addForce(ofVec2f(ofRandom(-1,1)*10,ofRandom(0.5,-1)*10),ofRandom(20,50));
        o.setBoundingBox(ofRectangle(*boundingBoxPosition,boundingBoxDimension->x,boundingBoxDimension->y));
        o.addRotation(ofRandom(-1,1)*2);
        particles.push_back(o);
    }
   
    
    if(bUseSerial){
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    int baud = 9600;//115200;
    serial.setup(0, baud); //open the first device
    
    // serial.setup("/dev/tty.usbserial-A70060V8", 9600);
    serial.startContinuousRead();
    ofAddListener(serial.NEW_MESSAGE,this,&ofApp::onNewMessage);
    
    message = "";
    }
    
    
    
    minslider = new ofxDatGuiSlider("MIN", 0, 1000, 20);
    minslider->setWidth(600, .2); // make label area 20% of width //
    minslider->setPosition(0, 200);
    minslider->onSliderEvent(this, &ofApp::onSliderEvent);
 
    maxslider = new ofxDatGuiSlider("MAX", 0, 1000, 20);
    maxslider->setWidth(600, .2); // make label area 20% of width //
    maxslider->setPosition(0, 250);
    maxslider->onSliderEvent(this, &ofApp::onSliderEvent);
    
    sphere.setRadius(300);
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    minslider->update();
    maxslider->update();

    
    for(int i=0;i<videos.size();i++){
        videos[i]->update();
    }
    
    lastvideo->update();
    thisvideo->update();
    nextvideo->update();
    
  //  video->update();

    //videos[videoIndex%videos.size()]->update();
    
    for(int i=0;i<particles.size();i++){
        particles[i].update();
    }

    
    
    if(bUseSerial)cout<<datamanager.getFloatAverage()<<endl;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofPushStyle();
   // ofTranslate(1920, 0);
    ofTranslate(0, 0);

    // ofScale(0.5,0.5);
     //videos[videoIndex%videos.size()]->draw();
    thisvideo->draw();
    ofSetColor(255,0,0);

    ofDrawLine(0, 0, 0, 1080);

  //  video->draw();
    ofPopStyle();
    ofPopMatrix();
    
    //ofEnableBlendMode(OF_BLENDMODE_SCREEN);
   // ofEnableAlphaBlending();
    
    
    
    ofPushMatrix();
    for(int i=0;i<particles.size();i++){
        particles[i].draw();
    }
    ofPopMatrix();
  //  ofEnableBlendMode(OF_BLENDMODE_SCREEN);
   if(bShowMask)mask.draw(0,0);
   // ofDrawRectangle(*boundingBoxPosition,boundingBoxDimension->x,boundingBoxDimension->y);
    if(debug){
        //cout<<videos[videoIndex%videos.size()]->getPosition()<<endl;
        //float w=ofMap(videos[videoIndex%videos.size()]->getPosition(),0,1,0,1080);
        float w=ofMap(thisvideo->getPosition(),0,1,0,1080);

        ofPushStyle();
        ofFill();
        ofSetColor(255,0,0);
        ofDrawRectangle(0, 0,w, 50);
        ofPopStyle();
    }
    
    
    
    
    if(bShowGui){
        minslider->draw();
        maxslider->draw();
    }
    

    
    
    
   /* cam.begin();

    ofDisableArbTex();
    //sphere.setPosition(ofGetWidth()*.5, ofGetHeight()*.5, 0);
    ofTexture tex=thisvideo->introClip->getTextureReference();
    //mTex.allocate(tex);
   // tex.bind();
    sphere.rotate(spinX, 1.0, 0.0, 0.0);
    sphere.rotate(spinX, 0.0, 1.0, 0.0);
   // texImage.getTexture().bind();
    mTex.bind();
    

    spinX+=0.1;
    sphere.draw();
    
    mTex.unbind();

  // tex.unbind();
    ofEnableArbTex();
    cam.end();
    
   // texImage.draw(0,0);*/
}




void ofApp::next(){
    
    float now=ofGetElapsedTimeMillis();
    if(nextDebounceTimer+nextDebounceDuration<now){
   // videos[videoIndex%videos.size()]->stopAndReset();
    
    // video index is for next video, so take old value for actual pic
    for(int i=0;i<particles.size();i++){
        particles[i].setNewImage(&images[videoIndex%videos.size()],ofRandom(imageFadeDuration));
    }
    
    videoIndex++;
   // videos[videoIndex%videos.size()]->setState(INTRO);
    lastvideo=thisvideo;
    
    lastvideo->closeVideos();
    
    thisvideo=nextvideo;
    thisvideo->setState(INTRO);
        
    nextvideo=videos[videoIndex%videos.size()];
    nextvideo->loadVideos();
        
    nextDebounceTimer=ofGetElapsedTimeMillis();
    
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





void ofApp::shake(){
    
    if(thisvideo->getState()==INTRO){
        for(int i=0;i<particles.size();i++){
            particles[i].addForce(ofVec2f(ofRandom(-1,1)*10,ofRandom(0.5,-1)*10),ofRandom(10));
            particles[i].setDampingDuration(ofRandom(5,10));
            particles[i].addRotation(ofRandom(-1,1)*10);
            }
    }else{
        for(int i=0;i<particles.size();i++){
            particles[i].addForce(ofVec2f(ofRandom(-1,1)*10,ofRandom(0.5,-1)*10),ofRandom(20,50));
            particles[i].addRotation(ofRandom(-1,1)*2);
            particles[i].setDampingDuration(ofRandom(5,10));

        }
        next();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='g'){
        bShowGui=!bShowGui;
        
    }
    
    if(key =='n'){
        next();
    }
    
    if(key =='N'){
     //   debugNext();
    }

    
    if(key=='s'){
        
        shake();
       
    }
    
    
    if(key=='d'){
        
        debug=!debug;
        
    }
    if(key=='m'){
        bShowMask=!bShowMask;
    }
    
    
    if(key=='B'){
        //  mover.setSlowDown(true);
        boundingBoxPosition->set(ofGetMouseX(),ofGetMouseY());
        Settings::get().save("data.json");
        
        
        for(int i=0;i<particles.size();i++){
            particles[i].setBoundingBox(ofRectangle(*boundingBoxPosition,boundingBoxDimension->x,boundingBoxDimension->y));
            
        }
        
    }
    
    
    if(key=='D'){
        boundingBoxDimension->set(ofGetMouseX()-boundingBoxPosition->x,ofGetMouseY()-boundingBoxPosition->y);
        Settings::get().save("data.json");
        
        for(int i=0;i<particles.size();i++){
            particles[i].setBoundingBox(ofRectangle(*boundingBoxPosition,boundingBoxDimension->x,boundingBoxDimension->y));
        }
    }
    
    
    if(key=='f'){
        ofToggleFullscreen();
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


void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    if(e.target == minslider){
        ofSetBackgroundColor(ofColor::white*e.scale);
        cout << e.target->getLabel() << " value = "; e.target->printValue();
    }   else if (e.target == maxslider){
        cout << e.target->getLabel() << " value = "; e.target->printValue();
    }  /* else if (e.target == sliderFloat){
        cout << e.target->getLabel() << " value = "; e.target->printValue();
    }*/
}




void ofApp::onNewMessage(string & message)
{
   // cout << "onNewMessage, message: " << message << "\n";
   string firstWord= ofSplitString(message, ",")[0];
    
    
    
    
    if(videos[videoIndex%videos.size()]->getState()==INTRO){
        
        
        if(ofToFloat(firstWord)> 500 || ofToFloat(firstWord)< 200){
            
            // if(ofToFloat(firstWord)> maxslider->getValue() || ofToFloat(firstWord)< minslider->getValue()){
            for(int i=0;i<particles.size();i++){
                particles[i].addForce(ofVec2f(ofRandom(-1,1),ofRandom(0.5,-1)),message[1]/10);
            }
        }
    }else{
        
        
        if(ofToFloat(firstWord)> 500 || ofToFloat(firstWord)< 200){
            
            // if(ofToFloat(firstWord)> maxslider->getValue() || ofToFloat(firstWord)< minslider->getValue()){
            for(int i=0;i<particles.size();i++){
                particles[i].addForce(ofVec2f(ofRandom(-1,1),ofRandom(0.5,-1)),message[1]/10);
            }
        }
        next();
    }
    
    
    
    
    
    
    
    
  
    datamanager.addFloatValue(ofToFloat(firstWord));
    
}
