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

