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
#include "ofxJSON.h"


class tracker{
public:
    tracker();
    ~tracker();
    
    // gui and settings
    string jsonParametersFilePath;
    ofxPanel gui;
    string guiFileName;
    ofParameterGroup parameters;
    bool isShowGui;
    
    // timeline
    string trackFolderName;
    ofxTimeline timeline;
    ofxTLVideoTrack* videoTrack;
    
    // tracks
    ofParameter<int> trackCount;
    ofParameter<bool> isDrawEntirePath;
    vector<track> tracks;
    int curTrack;
    
    void onIsDrawEntirePath(bool &b);
    
    void setup();
    void setupGui();
    void setupTimeline();
    
    void saveJsonParameters();
    
    void loadTracks();
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
