OF 0.9.8
### Installation

to clone with submodules (forked localAddons used):

`git clone --recursive https://github.com/GordeyChernyy/timelineTracker`

after updating project using projectGenerator go to Build Settings > Preprocessor macros > add `TIMELINE_VIDEO_INCLUDED=1`

#### Addons

[ofxMSATimer](https://github.com/obviousjim/ofxMSATimer)

[ofxRange](https://github.com/Flightphase/ofxRange)

[ofxTextInputField](https://github.com/Flightphase/ofxTextInputField)

[ofxTimecode](https://github.com/YCAMInterlab/ofxTimecode)

[ofxTween](https://github.com/arturoc/ofxTween)

[ofxJson](https://github.com/jefftimesten/ofxJSON.git)

ofxGui

ofxXmlSettings

### Usage

Hold alt key and move mouse to move keyframe

Shift - show/hide timeline

Tab - show/hide gui

Spacebar - play

d f - jump through the 5frames

e r - previous/next frame

c v - previous/next keyframe

t - create new track

y - delete track

a z - select previous/next track

x - delete keyframe

ofxTimeline stores track data in two files `timeline0_trackname_X.xml` for x values and `timeline0_trackname_Y.xml` for y. Values are normalized depending on settings in range in `tracker::addTrack`:

```C++
t.posX = timeline.addCurves(name + " X", ofRange(0.0, ofGetWidth()), 1.0);
t.posY = timeline.addCurves(name + " Y", ofRange(0.0, ofGetHeight()), 1.0);

```
