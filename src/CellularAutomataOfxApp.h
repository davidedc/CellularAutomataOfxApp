#pragma once

#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxStateMachine.h"
#include "SharedData.h"

class CellularAutomataOfxApp : public ofxiPhoneApp{
    
public:
    void setup();
    void update();
    void draw();

    void exit();

    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);

    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);

    bool retina;

    int w;  // width
    int h;  // height


    unsigned char* pixels;  // pixel array

    ofImage output;         // output image

    void calculateBitmap();
    CellularAutomataOfxApp(CGSize passed_screenSize);
    CGSize screenSize;
    ofTrueTypeFont testFont;

private:
    itg::ofxStateMachine<SharedData> stateMachine;


};


