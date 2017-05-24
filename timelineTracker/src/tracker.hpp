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
    ofParameter<bool> isDrawEntirePath;
    vector<track> tracks;
    int curTrack;
    
    // keyframe
    bool isDrawNearestKey;
    int nearestKeyFrameNum;
    ofVec2f nearestKeyPos;
    
    void keyPressed(ofKeyEventArgs &arg);
    void keyReleased(ofKeyEventArgs &arg);
    
    void onIsDrawEntirePath(bool &b);
    
    void mouseMoved(float x, float y);
    void mouseClicked(float x, float y);
    
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
    
    void jumpToStart();
    
    void goToNFrames(int count);
    void goToNFramesFromZero(int count);
    void goToNearest(float x, float y);
    
    void togglePlay();
    void toggleShowGui();
    void toggleShowTimeline();

    void draw();
    void drawTracks();
    void drawNearestKey();
    void drawTarget(ofVec2f pos);
    void drawHalfLine(); // draw only part of line based on current time
};

#endif /* tracker_hpp */
