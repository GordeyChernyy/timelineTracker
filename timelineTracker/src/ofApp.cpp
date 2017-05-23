#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    tracker.setup();
    ofSetBackgroundColor(0);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    tracker.draw();
    
    ofFill();
    
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'x') {
        tracker.deleteKey();
    }
    if(key == 'e'){
        tracker.prevFrame();
    }
    if(key == 'r'){
        tracker.nextFrame();
    }
    if(key == 'f'){
        tracker.nextNFrame();
    }
    if(key == 'd'){
        tracker.prevNFrame();
    }
    if(key == ' '){
        tracker.togglePlay();
    }
    if(key == 'c'){
        tracker.prevKeyFrame();
    }
    if(key == 'v'){
        tracker.nextKeyFrame();
    }
    if(key == 'a'){
        tracker.nextTrack();
    }
    if(key == 'z'){
        tracker.prevTrack();
    }
    if(key == 't'){
        tracker.addTrack(ofSystemTextBoxDialog("New track name:"));
    }
    if(key == OF_KEY_SHIFT){
        tracker.toggleShowTimeline();
    }
    if(key == 'y'){
        tracker.removeSelectedTrack();
    }
    if(key == OF_KEY_TAB){
        tracker.toggleShowGui();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    tracker.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    tracker.mouseClicked(x, y);
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
