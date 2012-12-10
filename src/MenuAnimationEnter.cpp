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
    
    
    // debug draw of tight bounding box around the write
    //ofSetColor(125,0,0,179);
    //ofRect(15, 270 - ascender, appTitleStringBoundingBox.width, appTitleStringBoundingBox.height);
    
    ofSetColor(0,0,0,179);
    
    int marginSize = getSharedData().marginSize;
    int ascender = getSharedData().ascender;
    int upperVerticalMarginSize = getSharedData().upperVerticalMarginSize;
    int totalVerticalMarginSize = getSharedData().totalVerticalMarginSize;
    ofRectangle appTitleStringBoundingBox =  getSharedData().appTitleStringBoundingBox;

    
    ofRect(15 - marginSize, 270 - ascender - upperVerticalMarginSize, appTitleStringBoundingBox.width + 2*marginSize, appTitleStringBoundingBox.height + totalVerticalMarginSize);
    
    
    ofDisableAlphaBlending();
    ofSetColor(255);
    // text origin is on the baseline. So for example
    // all the descenders (like in "g" and "j") will be BELOW
	getSharedData().testFont.drawString(getSharedData().appTitleString, 15 + horizSlide, 270);
    
    if (framesIntoTheAnimtion > 60){
        changeState("firstScreenState");
    }

    
}

string MenuAnimationEnter::getName()
{
	return "MenuAnimationEnter";
}

