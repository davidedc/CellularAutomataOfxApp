/*
 *  FirstScreenState.cpp
 *
 *  Copyright (c) 2011, Neil Mendoza, http://www.neilmendoza.com
 *  All rights reserved. 
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met: 
 *  
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 *  * Neither the name of 16b.it nor the names of its contributors may be used 
 *    to endorse or promote products derived from this software without 
 *    specific prior written permission. 
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 *  POSSIBILITY OF SUCH DAMAGE. 
 *
 */
#include "FirstScreenState.h"

void FirstScreenState::setup() {
}

void FirstScreenState::update(){
}

void FirstScreenState::draw() {

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
	getSharedData().testFont.drawString(appTitleString, 15, 270);
    

}

string FirstScreenState::getName()
{
	return "firstScreenState";
}

void FirstScreenState::touchDown(ofTouchEventArgs & touch)
{
	changeState("animateAutomatonState");
}
