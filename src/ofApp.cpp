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
}

//--------------------------------------------------------------
void ofApp::update(){
    /*for(int i=0;i<videos.size();i++){
        videos[i]->update();
    }*/
    video->update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    video->draw();
}




void ofApp::next(){
    if(video->getState()==IDLE){
        videoIndex++;
        video->stopAndReset();
        if(videos.size()>0){
            video=videos[videoIndex%videos.size()];
        }
        video->setState(INTRO);
    }
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
