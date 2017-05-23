//
//  track.cpp
//  timelineTracker
//
//  Created by Gordey on 5/22/17.
//
//

#include "track.hpp"
void track::draw(){
    isDrawEntirePath ? drawLine() : drawTimeBasedLine();
    drawPlayHead();
}

void track::setup(){

}
ofVec2f track::getPos(){
    return ofVec2f(posX->getValue(), posY->getValue());
}
void track::drawTimeBasedLine(){
    ofxTimeline *timeline = posX->getTimeline();
    float time = timeline->getCurrentTimeMillis();
    
    vector<ofxTLKeyframe*> keyframesX = posX->getKeyframes();
    vector<ofxTLKeyframe*> keyframesY = posY->getKeyframes();
    
    ofPolyline line;
    
    for (int i = 0; i < keyframesX.size(); i++) {
        float keyTime = keyframesX[i]->time;
        
        if(keyTime>time){
            line.addVertex(getPos());
            break;
        }
        
        float x = ofMap(keyframesX[i]->value, 0, 1, 0, ofGetWidth(), true);
        float y = ofMap(keyframesY[i]->value, 0, 1, 0, ofGetHeight(), true);
        float r = ofMap(i, 0, keyframesX.size(), 1, 8);
        line.addVertex(x, y);
    }
    
    if(isActive) ofSetColor(ofColor::white);
    else ofSetColor(ofColor::gray);
    
    line.draw();
}
void track::drawLine(){
    vector<ofxTLKeyframe*> keyframesX = posX->getKeyframes();
    vector<ofxTLKeyframe*> keyframesY = posY->getKeyframes();
    
    ofPolyline line;
    
    for (int i = 0; i < keyframesX.size(); i++) {
        float x = ofMap(keyframesX[i]->value, 0, 1, 0, ofGetWidth(), true);
        float y = ofMap(keyframesY[i]->value, 0, 1, 0, ofGetHeight(), true);
        float r = ofMap(i, 0, keyframesX.size(), 1, 8);
        line.addVertex(x, y);
    }
    
    if(isActive) ofSetColor(ofColor::white);
    else ofSetColor(ofColor::gray);
    
    line.draw();
}
void track::drawPlayHead(){
    if(isActive) ofSetColor(ofColor::red);
    else ofSetColor(ofColor::gray);
    
    ofDrawCircle(getPos(), 5);
}