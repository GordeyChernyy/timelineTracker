//

//  tracker.cpp
//  timelineTracker
//
//  Created by Gordey on 5/22/17.
//
//

#include "tracker.hpp"

tracker::tracker(){
    
}
tracker::~tracker(){
    gui.saveToFile(guiFileName);
    saveJsonParameters();
    ofLog() << "gui.saveToFile: " << guiFileName;
}
// save
void tracker::saveJsonParameters(){
    // load track names
    ofxJSONElement jsonTracks;
    for(auto &t : tracks){
        jsonTracks.append(t.name);
    }
    
    // save file
    ofxJSON p;
    p["tracks"] = jsonTracks;
    p.save("jsonParameters.json", true);
}
// setup
void tracker::setup(){
    // set video size
    videoWidth = ofGetWidth();
    videoHeight = ofGetHeight();
    
    // init
    trackFolderName = "tracks";
    jsonParametersFilePath = "jsonParameters.json";
    isShowGui = true;
    curTrack = 0;
    nearestKeyFrameNum = 0;

    // setup
    setupTimeline();
    toggleShowTimeline();
    setupGui();
    loadTracks();
    ofRegisterKeyEvents(this);
}
void tracker::setupGui(){
    guiFileName = "TrackerSettings.xml";
    
    isDrawEntirePath.addListener(this, &tracker::onIsDrawEntirePath);
    
    parameters.setName("TrackerParameters");
    parameters.add(isDrawEntirePath.set("isDrawEntirePath", true));
    
    gui.setup(parameters, guiFileName);
    gui.loadFromFile(guiFileName);
    
}
// mouse
void tracker::mouseMoved(float x, float y){
    if(ofGetKeyPressed(OF_KEY_ALT) && !timeline.getIsPlaying()) addKey(x, y);
    
    if(ofGetKeyPressed(OF_KEY_COMMAND) && !timeline.getIsPlaying()){
        goToNearest(x, y);
        isDrawNearestKey = true;
    }else{
        isDrawNearestKey = false;
    }
}
void tracker::mouseClicked(float x, float y){
    
}
// key
void tracker::keyPressed(ofKeyEventArgs &arg){
    
}
void tracker::keyReleased(ofKeyEventArgs &arg){
    if(arg.key == OF_KEY_COMMAND){
        goToNFramesFromZero(nearestKeyFrameNum+1);
    }
}
// onGui
void tracker::onIsDrawEntirePath(bool &b){
    for(auto &t : tracks){
        t.isDrawEntirePath = b;
    }
}
// timeline control
void tracker::setupTimeline(){
    
    //set the timeline up with some default values
    
    timeline.setup();
    
    timeline.setFrameRate(30);
    //set big initial duration, longer than the video needs to be
    timeline.setDurationInFrames(20000);
    timeline.setLoopType(OF_LOOP_NORMAL);
    
    // load video
    videoTrack = timeline.addVideoTrack("Video", "fingers.mov");
    timeline.setFrameRate(videoTrack->getPlayer()->getTotalNumFrames()/videoTrack->getPlayer()->getDuration());
    timeline.setDurationInFrames(videoTrack->getPlayer()->getTotalNumFrames());
    timeline.setTimecontrolTrack(videoTrack); //video playback will control the time
    timeline.bringTrackToTop(videoTrack);
    
//    timeline.disableEvents();
    
}
void tracker::addTrack(string name){
    track t;
    t.name = name;
    t.w = videoWidth;
    t.h = videoHeight;
    t.posX = timeline.addCurves(name + " X", ofRange(0.0, videoWidth), 1.0);
    t.posY = timeline.addCurves(name + " Y", ofRange(0.0, videoHeight), 1.0);
    t.posX->setDefaultEasingType(2);
    t.posY->setDefaultEasingType(2);
    t.posX->setDefaultEasingFunction(0);
    t.posY->setDefaultEasingFunction(0);
    t.setup();
    
    tracks.push_back(t);
    
    if(tracks.size()>0) nextTrack();
    
    setSelected();
}
void tracker::removeSelectedTrack(){
    ofLog() << "remove";
    tracks.erase(tracks.begin()+curTrack);
    prevTrack();
}
void tracker::addKey(float x, float y){
    tracks[curTrack].posX->addKeyframe(x);
    tracks[curTrack].posY->addKeyframe(y);    
}
void tracker::deleteKey(){
    ofxTLKeyframe* keyFrameX = tracks[curTrack].posX->getKeyframeAtMillis(timeline.getCurrentTimeMillis());
    ofxTLKeyframe* keyFrameY = tracks[curTrack].posY->getKeyframeAtMillis(timeline.getCurrentTimeMillis());
    tracks[curTrack].posX->deleteKeyframe(keyFrameX);
    tracks[curTrack].posY->deleteKeyframe(keyFrameY);
}
void tracker::jumpToStart(){
    timeline.getVideoPlayer("Video")->firstFrame();
}
void tracker::prevFrame(){
    timeline.getVideoPlayer("Video")->previousFrame();
}
void tracker::nextFrame(){
    timeline.getVideoPlayer("Video")->nextFrame();
}
void tracker::prevNFrame(){
    for (int i = 0; i < 5; i++) {
        timeline.getVideoPlayer("Video")->previousFrame();
    }
}
void tracker::nextNFrame(){
    for (int i = 0; i < 5; i++) {
        timeline.getVideoPlayer("Video")->nextFrame();
    }
}
void tracker::nextKeyFrame(){
    float time = timeline.getCurrentTimeMillis();
    int framesTotal = videoTrack->getPlayer()->getTotalNumFrames();
    float duration = videoTrack->getPlayer()->getDuration();
    
    for (int i = 0; i < tracks[curTrack].posX->getKeyframes().size(); i++) {
        float keyframeTime = tracks[curTrack].posX->getKeyframes()[i]->time;
        if(keyframeTime>time){
            int f = (framesTotal*keyframeTime)/duration/1000;
            int curFrame = timeline.getCurrentFrame();
            goToNFrames(f-curFrame);
            return;
        }
    }
}
void tracker::prevKeyFrame(){
    float time = timeline.getCurrentTimeMillis();
    int framesTotal = videoTrack->getPlayer()->getTotalNumFrames();
    float duration = videoTrack->getPlayer()->getDuration();
    
    for (int i = tracks[curTrack].posX->getKeyframes().size()-1; i >= 0; i--) {
        float keyframeTime = tracks[curTrack].posX->getKeyframes()[i]->time;
        if(keyframeTime<time){
            int f = (framesTotal*keyframeTime)/duration/1000;
            int curFrame = timeline.getCurrentFrame();
            goToNFrames(-(curFrame-f));
            return;
        }
    }
}
void tracker::nextTrack(){
    curTrack++;
    curTrack = MIN(tracks.size()-1, curTrack);
    setSelected();
}
void tracker::prevTrack(){
    curTrack--;
    curTrack = MAX(0, curTrack);
    setSelected();
}
void tracker::loadTracks(){
    ofxJSON p;
    if(ofFile(jsonParametersFilePath)){
        p.open(jsonParametersFilePath);
        for (int i = 0; i < p["tracks"].size(); i++) {
            string name =  p["tracks"][i].asString();
            addTrack(name);
        }
    }else{
        ofLog() << jsonParametersFilePath << " file not found";
    }
}
void tracker::setSelected(){
    for(auto &t : tracks){
        t.isActive = false;
    }
    tracks[curTrack].isActive = true;
}
void tracker::goToNFrames(int count){
    if(count>0){
        for (int i = 0; i < count; i++) {
            nextFrame();
        }
    }else{
        ofLog() << abs(count);
        for (int i = 0; i < abs(count); i++) {
            prevFrame();
        }
    }
}
void tracker::goToNFramesFromZero(int count){
    timeline.getVideoPlayer("Video")->stop();
    for (int i = 0; i < count; i++) {
        nextFrame();
    }
}
void tracker::goToNearest(float x, float y){
    ofVec2f m(x, y);
    
    int framesTotal = videoTrack->getPlayer()->getTotalNumFrames();
    float duration = videoTrack->getPlayer()->getDuration();
    
    track *t = &tracks[curTrack];
    for (int i = 0; i < t->posX->getKeyframes().size(); i++) {
        ofxTLKeyframe* kx = t->posX->getKeyframes()[i];
        ofxTLKeyframe* ky = t->posY->getKeyframes()[i];
        
        float x = ofMap(kx->value, 0, 1, 0, videoWidth, true);
        float y = ofMap(ky->value, 0, 1, 0, videoHeight, true);

        float keyframeTime = kx->time;
        
        ofVec2f p(x, y);
        
        if(m.distance(p)<30){
            nearestKeyPos = p;
            nearestKeyFrameNum = (framesTotal*keyframeTime)/duration/1000;
        }
    }
}
void tracker::togglePlay(){
    if(timeline.getVideoPlayer("Video")->isPlaying()){
        timeline.getVideoPlayer("Video")->setPaused(true);
    }else{
        timeline.getVideoPlayer("Video")->play();
        
    }
}
void tracker::toggleShowTimeline(){
    if(timeline.getIsShowing()) timeline.hide();
    else timeline.show();
}
void tracker::toggleShowGui(){
    isShowGui ^= true;
}
// draw
void tracker::draw(){
    timeline.getVideoPlayer("Video")->draw(0, 0);
    timeline.draw();
    drawTracks();
    if(isShowGui) gui.draw();
    if(isDrawNearestKey) drawNearestKey();
//    drawHalfLine();
}
void tracker::drawNearestKey(){
    ofSetColor(ofColor::green);
    ofDrawCircle(nearestKeyPos, 5);
    ofDrawBitmapString(ofToString(nearestKeyFrameNum), nearestKeyPos + ofVec2f(0, -20));
}
void tracker::drawTracks(){
    for(auto &t : tracks){
        t.draw();
    }
}
void tracker::drawTarget(ofVec2f pos){
    ofNoFill();
    ofSetColor(ofColor::white);
    float width = 30;
    
    ofPushMatrix();
    ofTranslate(pos);
    ofDrawCircle(0, 0, width/3);
    ofDrawLine(-width/2, 0, width/2, 0);
    ofDrawLine(0, -width/2, 0, width/2);
    ofPopMatrix();
}
void tracker::drawHalfLine(){
    float step = 0.1;
    float curPct = ofMap( timeline.getCurrentTimeMillis(), 0, videoTrack->getPlayer()->getDuration()*1000, 0, 1);
    float pctStart = MAX(0, curPct-step);
    float pctEnd = MIN(1, curPct+step);
    
    ofPolyline line;
    for (float i = pctStart; i < pctEnd; i+=0.001) {
        float x = tracks[curTrack].posX->getValueAtPercent(i);
        float y = tracks[curTrack].posY->getValueAtPercent(i);
        line.addVertex(x, y);
    }
    ofSetColor(ofColor::green);
    line.draw();
    
    ofSetColor(ofColor::white);
}
