//
//  tracker.hpp
//  timelineTracker
//
//  Created by Gordey on 5/22/17.
//
//

#ifndef tracker_hpp
#define tracker_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxTimeline.h"
#include "ofxTLAudioTrack.h"
#include "ofxTLVideoTrack.h"

#include "track.hpp"



class tracker{
public:
    tracker();
    
    ofxPanel gui;
    ofParameterGroup parameters;
    ofParameter<bool> isDrawEntirePath;
    bool isShowGui;
    
    ofxTimeline timeline;
    ofxTLVideoTrack* videoTrack;
    
    vector<track> tracks;
    int curTrack;
    
    void onIsDrawEntirePath(bool &b);
    
    void setup();
    void setupGui();
    void setupTimeline();
    
    void addTrack(string name);
    void removeSelectedTrack();
    
    void addKey(float x, float y);
    void deleteKey();
    
    void prevFrame();
    void nextFrame();
    
    void prevKeyFrame();
    void nextKeyFrame();
    
    void prevNFrame();
    void nextNFrame();
    
    void nextTrack();
    void prevTrack();
    void setSelected();
    
    void goToNFrames(int count);
    
    void togglePlay();
    void toggleShowGui();
    void toggleShowTimeline();

    void draw();
    void drawTracks();
    void drawTarget(ofVec2f pos);
    void drawHalfLine(); // draw only part of line based on current time
};

#endif /* tracker_hpp */
