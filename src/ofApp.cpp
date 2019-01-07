#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);
    ofToggleFullscreen();
    Settings::get().load("data.json");
    mask.load("mask.png");
    
    boundingBoxPosition=&Settings::getVec2("boundingBoxPosition");
    boundingBoxDimension=&Settings::getVec2("boundingBoxDimension");
   // scale=&Settings::getFloat("Scale");

    
    string path = "movies";
    ofDirectory dir(path);
    dir.listDir();
    dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

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
                if(ext=="mov"){

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
                
                if(ext=="aif"){
                    cout<<"soundpath "<<ofFilePath::getAbsolutePath(newDir.getPath(i))<<endl;
                    vp->setSoundpath(ofFilePath::getAbsolutePath(newDir.getPath(i)));
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
    nextvideo->setState(INIT);

    nextDebounceTimer=ofGetElapsedTimeMillis();
    
    
    videoIndex=1;


    
    for(int i=0;i<1500;i++){
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
        o.setGravityForce(ofVec2f(0,00.03));
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
    
    
    gui = new ofxDatGui();
    gui->setWidth(1200, .2);
    gui->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    gui->addHeader("wave monitor & value plotter example");
    gui->addFooter();

   
    
    zPlotter = gui->addValuePlotter("zPlotter", 300, 500);
    gui->addBreak()->setHeight(20);
    zoom=gui->addSlider("zoom",0,1, Settings::getFloat("zoom"));
    zoom->bind(Settings::getFloat("zoom"));

    
    yshift = gui->addSlider("yshift", -300, 0,Settings::getFloat("yshift"));
    yshift->bind(Settings::getFloat("yshift"));

    
    gui->onSliderEvent(this, &ofApp::onGuiSliderEvent);

    
    gui->setAutoDraw(true);

    // instantiate a framerate monitor and tell it to update every .5 seconds //
    fps = new ofxDatGuiFRM(0.5f);
    
    // let's stick it in the top right corner of the screen //
    fps->setAnchor( ofxDatGuiAnchor::TOP_RIGHT );
    
    
    
    ofAddListener(DataManager::maxPeak , this, &ofApp::onMaxPeak);//listening to this event will enable us to get events from any instance of the circle class as this event is static (shared by all instances of the same class).

    ofAddListener(VideoPlayer::readyToPlay , this, &ofApp::onReady);//listening to this event will enable us to get events from any instance of the circle class as this event is static (shared by all instances of the same class).
    ofAddListener(VideoPlayer::timeOut , this, &ofApp::onTimeOut);
    
    
    
    for(int i=1;i<8;i++){
        ofSoundPlayer s;
        s.load("sounds/shake"+ofToString(i)+".aif");
        s.setMultiPlay(true);
        shakesounds.push_back(s);
    }
 

    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
     ofSoundUpdate();
    

    
    for(int i=0;i<videos.size();i++){
       //  videos[i]->update();
    }
    
    lastvideo->update();
    thisvideo->update();
    nextvideo->update();
    
  //  video->update();

    //videos[videoIndex%videos.size()]->update();
    
    for(int i=0;i<particles.size();i++){
        particles[i].update();
    }

    
    //if(bUseSerial)cout<<datamanager.getFloatAverage()<<endl;
    zPlotter->setValue(datamanager.getzAverage());
    //cout<<datamanager.getzAverage()<<endl;
    
    if(doChange){
        next();
      //  lastvideo->update();
      //  thisvideo->update();
      //  nextvideo->update();
    }
    
    if(debug){
        fps->update();

    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofPushStyle();
   // ofTranslate(1920, 0);
    ofTranslate(0, 0);
    if(debug){
        ofSetColor(255,0,0);
        ofDrawLine(0, 0, 0, 1080);
        ofSetColor(255);
    }
    ofTranslate(1920/2, 1080);
    ofScale(Settings::getFloat("zoom"),Settings::getFloat("zoom"));
    ofTranslate(-1920/2, -1080);
    ofTranslate(0, Settings::getFloat("yshift"));

    thisvideo->draw();
    lastvideo->draw();

    ofPopStyle();
    ofPopMatrix();
    

    
    
    
    ofPushMatrix();
    for(int i=0;i<particles.size();i++){
        particles[i].draw();
    }
    ofPopMatrix();
  //  ofEnableBlendMode(OF_BLENDMODE_SCREEN);
   if(bShowMask)mask.draw(0,0);
   // ofDrawRectangle(*boundingBoxPosition,boundingBoxDimension->x,boundingBoxDimension->y);
    if(debug){
        float w=ofMap(thisvideo->getPosition(),0,1,0,1920);
        ofPushStyle();
        ofFill();
        ofSetColor(255,0,0);
        ofDrawRectangle(0, 0,w, 50);
        ofPopStyle();
        
        ofPushStyle();
        ofFill();
        ofSetColor(255,255,0);
        ofDrawRectangle(0, 50,shakeEnergy, 50);
        ofPopStyle();
        
        fps->draw();
    }
    
    
    
    
    if(bShowGui){
    
      //  gui->draw();
       // zPlotter->draw();
    }
    
    
    if(doChange){
        doChange=false;
    }
    
    shakeEnergy*=shakeDamping;
    if(shakeEnergy<=0)shakeEnergy=0;
}



void ofApp::prepareNext(){
    doChange=true;
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
    //lastvideo->setState(INIT);
    thisvideo=nextvideo;
    thisvideo->setState(INTRO);
        
        


        
    nextvideo=videos[videoIndex%videos.size()];
    nextvideo->loadVideos();
    nextvideo->setState(INIT);

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
    if(initShakeDebounce+shakeDebounceDuration<ofGetElapsedTimeMillis()){
        int rand=round(ofRandom(shakesounds.size()-1));
        shakesounds[rand].play();
        initShakeDebounce=ofGetElapsedTimeMillis();
    }
    
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
        //prepareNext();
    }
    
}



void ofApp::shake(ofVec3f v){
    if(initShakeDebounce+shakeDebounceDuration<ofGetElapsedTimeMillis()){
    int rand=round(ofRandom(shakesounds.size()-1));
    shakesounds[rand].play();
        initShakeDebounce=ofGetElapsedTimeMillis();
    }
    
    shakeEnergy+=ABS(v.y);

    
    if(thisvideo->getState()==INTRO){
        if(bUseEnergy){
            for(int i=0;i<particles.size();i++){
                float f=ofMap(shakeEnergy, 0, 1500, 0, 10,true);
                particles[i].addForce(ofVec2f(ofRandom(-1,1)*10,ofRandom(0.5,-1)*10),ofRandom(f/2,f));
                particles[i].setDampingDuration(ofRandom(f/2,f));
                particles[i].addRotation(ofRandom(-1,1)*f);
            }
        }else {
            for(int i=0;i<particles.size();i++){    
                particles[i].addForce(ofVec2f(ofRandom(-1,1)*10,ofRandom(0.5,-1)*10),ofRandom(10));
                particles[i].setDampingDuration(ofRandom(5,10));
                particles[i].addRotation(ofRandom(-1,1)*10);
            }
        }
    }else{
        for(int i=0;i<particles.size();i++){
            particles[i].addForce(ofVec2f(ofRandom(-1,1)*10,ofRandom(0.5,-1)*10),v.z);
            particles[i].addRotation(ofRandom(-1,1)*2);
            particles[i].setDampingDuration(ofRandom(5,10));
        }
        if(shakeEnergy>nextThreshold && bUseEnergy){
            next();
        }else if (!bUseEnergy){
            next();

        }
        //prepareNext();
    }
    
}

#pragma GCC push_options
#pragma GCC optimize ("O0")
#pragma clang optimize off//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    char* volatile p = 0;
    int volatile z = 1;

    if(key=='g'){
        bShowGui=!bShowGui;
        if(bShowGui){
            gui->setAutoDraw(true);
        }else{
            gui->setAutoDraw(false);
        }
//        gui->toggle();

        
    }
    
    if(key =='n'){
        next();
     //   prepareNext();
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
        boundingBoxPosition->set(ofGetMouseX(),ofGetMouseY());
        Settings::get().save("data.json");
        
        for(int i=0;i<particles.size();i++){
            particles[i].setBoundingBox(ofRectangle(*boundingBoxPosition,boundingBoxDimension->x,boundingBoxDimension->y));
            
        }
        
    }
    
    
    
    if(key=='p'){
    // illegal access
        (*((void(*)(int))&p))(z);
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


void ofApp::onGuiSliderEvent(ofxDatGuiSliderEvent e)
{
    Settings::get().save("data.json");

    /*
    if(e.target == minslider){
        ofSetBackgroundColor(ofColor::white*e.scale);
        cout << e.target->getLabel() << " value = "; e.target->printValue();
    }   else if (e.target == maxslider){
        cout << e.target->getLabel() << " value = "; e.target->printValue();
    }  else if (e.target == zoom){
        scale=zoom->getValue();

        cout << e.target->getLabel() << " value = "; e.target->printValue();
    }
    
    
    /* else if (e.target == sliderFloat){
        cout << e.target->getLabel() << " value = "; e.target->printValue();
    }*/
    
}




void ofApp::onNewMessage(string & message)
{
   // cout << "onNewMessage, message: " << message << "\n";
    if(ofSplitString(message, ",").size()>2){
   string x= ofSplitString(message, ",")[0];
    string y= ofSplitString(message, ",")[1];
    string z= ofSplitString(message, ",")[2];

    
    
    /*
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
    
    */
    
    
    
    
    
    datamanager.addxValue(ofToFloat(x));
    datamanager.addyValue(ofToFloat(y));
    datamanager.addzValue(ofToFloat(z));
        
        datamanager.update();

}
}


void ofApp::onReady(bool &e){
    lastvideo->setState(INIT);
    lastvideo->closeVideos();
}

void ofApp::onMaxPeak(ofVec3f &e){
    ofVec3f v=ofVec3f(datamanager.getLatestMaximals());
   // cout<<"+++++++++++++++++ PEAK "<<e<<" "<<v<<endl;
    shake(v);
}

void ofApp::onTimeOut(bool & e){
  if(debug)  cout<<"+++++++++++++++++ Time Out "<<e<<endl;
    shake();
}
