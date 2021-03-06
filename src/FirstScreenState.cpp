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
    
    // Put the info from the global state into local variables.
    // We are not going to change these values so there WON'T be a need to
    // put these back into the global state later.
    int marginSize = getSharedData().marginSize;
    int ascender = getSharedData().ascender;
    int upperVerticalMarginSize = getSharedData().upperVerticalMarginSize;
    int totalVerticalMarginSize = getSharedData().totalVerticalMarginSize;
    ofRectangle appTitleStringBoundingBox =  getSharedData().appTitleStringBoundingBox;
    string appTitleString = getSharedData().appTitleString;
    
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
