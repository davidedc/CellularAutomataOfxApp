#include "MenuAnimationEnter.h"
#include "ofxEasingFunc.h"

void MenuAnimationEnter::setup() {
}

void MenuAnimationEnter::update(){
}

void MenuAnimationEnter::draw() {
    
    if (frameNumberAtStartOfAnimation == 0) {
        frameNumberAtStartOfAnimation = ofGetFrameNum();
    }

    int framesIntoTheAnimtion = ofGetFrameNum() - frameNumberAtStartOfAnimation;

	float t = ofClamp(framesIntoTheAnimtion / 60., 0, 1);
	
	// all functions take input 0. ~ 1., and outputs 0. ~ 1.
	float horizSlide = 60 * ofxEasingFunc::Cubic::easeInOut(t);
	
    cout << horizSlide;
    
    if (!backGroundImage.isAllocated()){
        if (getSharedData().isIpad) {
            if (getSharedData().isRetina) {
                backGroundImage.loadImage("Default-Portrait@2x~ipad.png");
                ofLog(OF_LOG_NOTICE, "loaded image " + ofToString(backGroundImage.isAllocated()));
            }
        }
    }
    
    ofBackground(0, 255, 0);
	//ofSetColor(255, 0, 0);
    backGroundImage.draw(0,0);
    
    //enable blending!
	//We are going to use a blend mode that adds
	//all the colors to white.
	ofEnableAlphaBlending();
	//glBlendFunc(GL_ONE, GL_ONE);
    
    string appTitleString = "Digital Forest";
    ofRectangle appTitleStringBoundingBox = getSharedData().testFont.getStringBoundingBox(appTitleString, 0,0);
    
    // calculate the horizontal margin size. Note that horizontal margin
    // size is easier than the vertical. Vertical margin size
    // has to deal with the presence of descenders, which skew the
    // perception of vertical centers.
    // Here for the horizontal margin size we simply calculate it
    // as the space that it would take to accommodate an additional "i"
    string appTitleStringWithSideMargins = "i"+appTitleString;
    ofRectangle appTitleStringBoundingBoxWithMargins = getSharedData().testFont.getStringBoundingBox(appTitleStringWithSideMargins, 0,0);
    int marginSize = appTitleStringBoundingBoxWithMargins.width - appTitleStringBoundingBox.width;
    
    // for the vertical margin size, the descenders and non-caps
    // letters complicate things.
    // If there is a descender in the string, then to be percieved as
    // vertically centered we have to add less
    // margin to the bottom than to the top. Otherwise the string will appear
    // to be too high.
    // On the other side, if there are no
    // descenders the margin at the top needs to be a bit
    // less than the usual because otherwise there is too much space above the
    // non-caps letters. So here are all the adjutments, overall.
    // For some weird optical reason, if there are descenders then the
    // extra space above the non-caps letters doesn't bother the eye.
    int ascender = appTitleStringBoundingBox.height;
    int upperVerticalMarginSize = marginSize;
    int totalVerticalMarginSize;
    
    if (appTitleString.find("g")!=string::npos ||
        appTitleString.find("j")!=string::npos ||
        appTitleString.find("q")!=string::npos ||
        appTitleString.find("p")!=string::npos ||
        appTitleString.find("y")!=string::npos
        ) {
        totalVerticalMarginSize = 1.5*marginSize;
        ascender *= 0.77;
    }
    else {
        totalVerticalMarginSize = 2*marginSize;
        // in theory for this adjustment below one would
        // want to check if the string is all made of caps
        // in which case the full top margin would be applied.
        upperVerticalMarginSize *= 0.8;
    }
    
    // debug draw of tight bounding box around the write
    //ofSetColor(125,0,0,179);
    //ofRect(15, 270 - ascender, appTitleStringBoundingBox.width, appTitleStringBoundingBox.height);
    
    ofSetColor(0,0,0,179);
    ofRect(15 - marginSize, 270 - ascender - upperVerticalMarginSize, appTitleStringBoundingBox.width + 2*marginSize, appTitleStringBoundingBox.height + totalVerticalMarginSize);
    
    
    ofDisableAlphaBlending();
    ofSetColor(255);
    // text origin is on the baseline. So for example
    // all the descenders (like in "g" and "j") will be BELOW
	getSharedData().testFont.drawString(appTitleString, 15 + horizSlide, 270);
    
    if (framesIntoTheAnimtion > 60){
        changeState("firstScreenState");
    }

    
}

string MenuAnimationEnter::getName()
{
	return "MenuAnimationEnter";
}

