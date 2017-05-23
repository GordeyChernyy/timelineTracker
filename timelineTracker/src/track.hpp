//
//  track.hpp
//  timelineTracker
//
//  Created by Gordey on 5/22/17.
//
//

#ifndef track_hpp
#define track_hpp

#include "ofMain.h"
#include "ofxTimeline.h"
#include "ofxTLAudioTrack.h"
#include "ofxTLVideoTrack.h"

class track{
public:
    string name;
    bool isActive;
    bool isDrawEntirePath;
    
    track(){
        isDrawEntirePath = false;
        isActive = false;
    }
    ofVec2f getPos();
    
    void setup();
    
    void draw();
    void drawTimeBasedLine();
    void drawLine();
    void drawPlayHead();
    
    ofxTLCurves* posX;
    ofxTLCurves* posY;
};
#endif /* track_hpp */
