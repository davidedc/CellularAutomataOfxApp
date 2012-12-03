/*
 *  AnimateAutomatonState.cpp
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
#include "AnimateAutomatonState.h"

void AnimateAutomatonState::update() {
	if (ofGetElapsedTimeMillis() - getSharedData().lastUpdate > 1000) {
		getSharedData().counter--;
		getSharedData().lastUpdate = ofGetElapsedTimeMillis();
	}
}

void AnimateAutomatonState::draw() {
    ofBackground(0,0,0,255);
    
	ofSetColor(255,255,255);
    calculateBitmap();
    
    // copies pixel into output image
    output.setFromPixels( getSharedData().pixels, getSharedData().screenWidthPixels, getSharedData().screenHeightPixels, OF_IMAGE_COLOR );
    // draw output image to screen
    output.draw(0,0);
    
    
    
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
    
    
    glFlush();

}

void AnimateAutomatonState::touchDown(ofTouchEventArgs & touch) {
	changeState("firstScreenState");
}

string AnimateAutomatonState::getName() {
	return "animateAutomatonState";
}

void AnimateAutomatonState:: calculateBitmap() {
    
    unsigned char *pixelsForAutomaton = getSharedData().pixels;
    int w = getSharedData().screenWidthPixels;
    int h = getSharedData().screenHeightPixels;

    ofLog(OF_LOG_NOTICE, "screen height: " + ofToString(getSharedData().screenHeightPixels));

    ofLog(OF_LOG_NOTICE, "calculating cellular automata pixmap ");
    
    for(int j=0; j<h*w*3; j++) {
        pixelsForAutomaton[j] = 255;
    }
    
    for(int j=0; j<w; j++) {
        unsigned char randomPixel;
        if (ofRandom(0,1)>0.75) {
            if (ofRandom(0,1)>0.5) {
                randomPixel = 0;
                pixelsForAutomaton[j*3 + 0] = randomPixel;
                pixelsForAutomaton[j*3 + 1] = randomPixel;
                pixelsForAutomaton[j*3 + 2] = randomPixel;
            }
            else {
                randomPixel = 125;
                pixelsForAutomaton[j*3 + 0] = randomPixel;
                pixelsForAutomaton[j*3 + 1] = randomPixel;
                pixelsForAutomaton[j*3 + 2] = randomPixel;
            }
        }
    }
    
    
    for(int i=0; i<(h-1); i++) {
        for(int j=i%2; j<(w-1); j+=2) {
            //pixelsForAutomaton[i*w*3 + j*3 + 0] = (unsigned char) 255*(j%8)*sin(counter);
            //pixelsForAutomaton[i*w*3 + j*3 + 1] = (unsigned char) 255*(i%8)*sin(counter);
            //pixelsForAutomaton[i*w*3 + j*3 + 2] = (unsigned char) 0;
            unsigned char pixel1 = 0;
            unsigned char pixel2 = 0;
            
            //pixel1 = int(red(get(l, counter)));
            //pixel2 = int(red(get(l+1, counter)));
            pixel1 = pixelsForAutomaton[(i)*w*3 + j*3 + 0];
            pixel2 = pixelsForAutomaton[(i)*w*3 + (j+1)*3 + 0];
            
            if (pixel1 < 126) {
                //fill(0);
                //rect(i, counter2, 1, 1);
                pixelsForAutomaton[(i)*w*3 + j*3 + 0] = (unsigned char) 0;
                pixelsForAutomaton[(i)*w*3 + j*3 + 1] = (unsigned char) 0;
                pixelsForAutomaton[(i)*w*3 + j*3 + 2] = (unsigned char) 0;
            }
            
            if (pixel2 < 126) {
                //fill(0);
                //rect(i+1, counter2, 1, 1);
                pixelsForAutomaton[(i)*w*3 + (j+1)*3 + 0] = (unsigned char) 0;
                pixelsForAutomaton[(i)*w*3 + (j+1)*3 + 1] = (unsigned char) 0;
                pixelsForAutomaton[(i)*w*3 + (j+1)*3 + 2] = (unsigned char) 0;
            }
            
            if (pixel1== 255 && pixel2== 255) { // OK
                // do nothing
            }
            
            else if (pixel1== 0 && pixel2== 0) { // OK
                //fill(125);
                //rect(i, counter2+1, 2, 1);
                pixelsForAutomaton[(i+1)*w*3 + (j)*3 + 0] = (unsigned char) 125;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 0] = (unsigned char) 125;
                
                pixelsForAutomaton[(i+1)*w*3 + (j)*3 + 1] = (unsigned char) 125;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 1] = (unsigned char) 125;
                pixelsForAutomaton[(i+1)*w*3 + (j)*3 + 2] = (unsigned char) 125;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 2] = (unsigned char) 125;
                
            }
            
            else if (pixel1== 125 && pixel2== 125) { // OK
                //fill(0);
                //rect(i, counter+1, 2, 1);
                pixelsForAutomaton[(i+1)*w*3 + (j)*3 + 0] = (unsigned char) 0;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 0] = (unsigned char) 0;
                
                pixelsForAutomaton[(i+1)*w*3 + (j)*3 + 1] = (unsigned char) 0;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 1] = (unsigned char) 0;
                pixelsForAutomaton[(i+1)*w*3 + (j)*3 + 2] = (unsigned char) 0;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 2] = (unsigned char) 0;
                
            }
            
            else if (pixel1== 125 && pixel2== 0) { // OK
                //fill(125);
                //rect(i, counter+1, 1, 1);
                pixelsForAutomaton[(i+1)*w*3 + (j)*3 + 0] = (unsigned char) 125;
                pixelsForAutomaton[(i+1)*w*3 + (j)*3 + 1] = (unsigned char) 125;
                pixelsForAutomaton[(i+1)*w*3 + (j)*3 + 2] = (unsigned char) 125;
                //fill(0);
                //rect(i+1, counter+1, 1, 1);
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 0] = (unsigned char) 0;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 1] = (unsigned char) 0;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 2] = (unsigned char) 0;
            }
            else if (pixel1== 0 && pixel2== 125) { // OK
                //fill(0);
                //rect(i, counter+1, 1, 1);
                pixelsForAutomaton[(i+1)*w*3 + (j)*3 + 0] = (unsigned char) 0;
                pixelsForAutomaton[(i+1)*w*3 + (j)*3 + 1] = (unsigned char) 0;
                pixelsForAutomaton[(i+1)*w*3 + (j)*3 + 2] = (unsigned char) 0;
                //fill(125);
                //rect(i+1, counter+1, 1, 1);
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 0] = (unsigned char) 125;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 1] = (unsigned char) 125;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 2] = (unsigned char) 125;
            }
            else if (pixel1== 0 && pixel2== 255) { // OK
                //fill(0);
                //rect(i+1, counter+1, 1, 1);
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 0] = (unsigned char) 0;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 1] = (unsigned char) 0;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 2] = (unsigned char) 0;
            }
            else if (pixel1== 125 && pixel2== 255) { // OK
                //fill(125);
                //rect(i, counter+1, 1, 1);
                pixelsForAutomaton[(i+1)*w*3 + (j+0)*3 + 0] = (unsigned char) 125;
                pixelsForAutomaton[(i+1)*w*3 + (j+0)*3 + 1] = (unsigned char) 125;
                pixelsForAutomaton[(i+1)*w*3 + (j+0)*3 + 2] = (unsigned char) 125;
            }
            else if (pixel1== 255 && pixel2== 0) { // OK
                //fill(0);
                //rect(i, counter+1, 1, 1);
                pixelsForAutomaton[(i+1)*w*3 + (j+0)*3 + 0] = (unsigned char) 0;
                pixelsForAutomaton[(i+1)*w*3 + (j+0)*3 + 1] = (unsigned char) 0;
                pixelsForAutomaton[(i+1)*w*3 + (j+0)*3 + 2] = (unsigned char) 0;
            }
            else if (pixel1== 255 && pixel2== 125) { // OK
                //fill(125);
                //rect(i+1, counter+1, 1, 1);
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 0] = (unsigned char) 125;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 1] = (unsigned char) 125;
                pixelsForAutomaton[(i+1)*w*3 + (j+1)*3 + 2] = (unsigned char) 125;
            }
        }
        
        
    }
    
}

