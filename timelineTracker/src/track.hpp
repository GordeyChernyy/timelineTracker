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
    
    track(){
        isActive = false;
    }
    ofVec2f getPos(){
        return ofVec2f(posX->getValue(), posY->getValue());
    }
    
    void setup();
    
    void draw();
    void drawLine();
    void drawPlayHead();
    
    ofxTLCurves* posX;
    ofxTLCurves* posY;
};
#endif /* track_hpp */
