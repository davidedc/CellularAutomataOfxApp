#include "CellularAutomataOfxApp.h"

//--------------------------------------------------------------
void CellularAutomataOfxApp::setup(){	
	ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_PORTRAIT);

    //ofSeedRandom();
    w = 1536;   // define width of screen
    h = 2048;  // define height of screen
    
    pixels = new unsigned char[w*h*3];  // pixel array

	// wishful thinking, this thing is very slow.
    ofSetFrameRate(60);
}


//--------------------------------------------------------------
void CellularAutomataOfxApp::update(){
    fillImage();
}

//--------------------------------------------------------------
void CellularAutomataOfxApp::draw(){
    ofBackground(0,0,0);
    // draw output image to screen
    output.draw(0,0);
    //glFlush();
}

//--------------------------------------------------------------
void CellularAutomataOfxApp::exit(){
    
}

//--------------------------------------------------------------
void CellularAutomataOfxApp::touchDown(ofTouchEventArgs & touch){

}


//--------------------------------------------------------------
void CellularAutomataOfxApp::touchMoved(ofTouchEventArgs & touch){

}


void CellularAutomataOfxApp::fillImage() {

    for(int j=0; j<h*w*3; j++) {
        pixels[j] = 255;
    }
    
    for(int j=0; j<w; j++) {
        unsigned char randomPixel;
        if (ofRandom(0,1)>0.75) {
            if (ofRandom(0,1)>0.5) {
                randomPixel = 0;
                pixels[j*3 + 0] = randomPixel;
                pixels[j*3 + 1] = randomPixel;
                pixels[j*3 + 2] = randomPixel;
            }
            else {
                randomPixel = 125;
                pixels[j*3 + 0] = randomPixel;
                pixels[j*3 + 1] = randomPixel;
                pixels[j*3 + 2] = randomPixel;
            }
        }
    }

    
    for(int i=0; i<(h-1); i++) {
        for(int j=i%2; j<(w-1); j+=2) {
            //pixels[i*w*3 + j*3 + 0] = (unsigned char) 255*(j%8)*sin(counter);
            //pixels[i*w*3 + j*3 + 1] = (unsigned char) 255*(i%8)*sin(counter);
            //pixels[i*w*3 + j*3 + 2] = (unsigned char) 0;
            unsigned char pixel1 = 0;
            unsigned char pixel2 = 0;
                
                //pixel1 = int(red(get(l, counter)));
                //pixel2 = int(red(get(l+1, counter)));
                pixel1 = pixels[(i)*w*3 + j*3 + 0];
                pixel2 = pixels[(i)*w*3 + (j+1)*3 + 0];
                
                if (pixel1 < 126) {
                    //fill(0);
                    //rect(i, counter2, 1, 1);
                    pixels[(i)*w*3 + j*3 + 0] = (unsigned char) 0;
                    pixels[(i)*w*3 + j*3 + 1] = (unsigned char) 0;
                    pixels[(i)*w*3 + j*3 + 2] = (unsigned char) 0;
                }
                
                if (pixel2 < 126) {
                    //fill(0);
                    //rect(i+1, counter2, 1, 1);
                    pixels[(i)*w*3 + (j+1)*3 + 0] = (unsigned char) 0;
                    pixels[(i)*w*3 + (j+1)*3 + 1] = (unsigned char) 0;
                    pixels[(i)*w*3 + (j+1)*3 + 2] = (unsigned char) 0;
                }
                
                if (pixel1== 255 && pixel2== 255) { // OK
                    // do nothing
                }
                
                else if (pixel1== 0 && pixel2== 0) { // OK
                    //fill(125);
                    //rect(i, counter2+1, 2, 1);
                    pixels[(i+1)*w*3 + (j)*3 + 0] = (unsigned char) 125;
                    pixels[(i+1)*w*3 + (j+1)*3 + 0] = (unsigned char) 125;

                    pixels[(i+1)*w*3 + (j)*3 + 1] = (unsigned char) 125;
                    pixels[(i+1)*w*3 + (j+1)*3 + 1] = (unsigned char) 125;
                    pixels[(i+1)*w*3 + (j)*3 + 2] = (unsigned char) 125;
                    pixels[(i+1)*w*3 + (j+1)*3 + 2] = (unsigned char) 125;

                }
            
                else if (pixel1== 125 && pixel2== 125) { // OK
                    //fill(0);
                    //rect(i, counter+1, 2, 1);
                    pixels[(i+1)*w*3 + (j)*3 + 0] = (unsigned char) 0;
                    pixels[(i+1)*w*3 + (j+1)*3 + 0] = (unsigned char) 0;

                    pixels[(i+1)*w*3 + (j)*3 + 1] = (unsigned char) 0;
                    pixels[(i+1)*w*3 + (j+1)*3 + 1] = (unsigned char) 0;
                    pixels[(i+1)*w*3 + (j)*3 + 2] = (unsigned char) 0;
                    pixels[(i+1)*w*3 + (j+1)*3 + 2] = (unsigned char) 0;

                }
                
                else if (pixel1== 125 && pixel2== 0) { // OK
                    //fill(125);
                    //rect(i, counter+1, 1, 1);
                    pixels[(i+1)*w*3 + (j)*3 + 0] = (unsigned char) 125;
                    pixels[(i+1)*w*3 + (j)*3 + 1] = (unsigned char) 125;
                    pixels[(i+1)*w*3 + (j)*3 + 2] = (unsigned char) 125;
                    //fill(0);
                    //rect(i+1, counter+1, 1, 1);
                    pixels[(i+1)*w*3 + (j+1)*3 + 0] = (unsigned char) 0;
                    pixels[(i+1)*w*3 + (j+1)*3 + 1] = (unsigned char) 0;
                    pixels[(i+1)*w*3 + (j+1)*3 + 2] = (unsigned char) 0;
                }
                else if (pixel1== 0 && pixel2== 125) { // OK
                    //fill(0);
                    //rect(i, counter+1, 1, 1);
                    pixels[(i+1)*w*3 + (j)*3 + 0] = (unsigned char) 0;
                    pixels[(i+1)*w*3 + (j)*3 + 1] = (unsigned char) 0;
                    pixels[(i+1)*w*3 + (j)*3 + 2] = (unsigned char) 0;
                    //fill(125);
                    //rect(i+1, counter+1, 1, 1);
                    pixels[(i+1)*w*3 + (j+1)*3 + 0] = (unsigned char) 125;
                    pixels[(i+1)*w*3 + (j+1)*3 + 1] = (unsigned char) 125;
                    pixels[(i+1)*w*3 + (j+1)*3 + 2] = (unsigned char) 125;
                }
                else if (pixel1== 0 && pixel2== 255) { // OK
                    //fill(0);
                    //rect(i+1, counter+1, 1, 1);
                    pixels[(i+1)*w*3 + (j+1)*3 + 0] = (unsigned char) 0;
                    pixels[(i+1)*w*3 + (j+1)*3 + 1] = (unsigned char) 0;
                    pixels[(i+1)*w*3 + (j+1)*3 + 2] = (unsigned char) 0;
                }
                else if (pixel1== 125 && pixel2== 255) { // OK
                    //fill(125);
                    //rect(i, counter+1, 1, 1);
                    pixels[(i+1)*w*3 + (j+0)*3 + 0] = (unsigned char) 125;
                    pixels[(i+1)*w*3 + (j+0)*3 + 1] = (unsigned char) 125;
                    pixels[(i+1)*w*3 + (j+0)*3 + 2] = (unsigned char) 125;
                }
                else if (pixel1== 255 && pixel2== 0) { // OK
                    //fill(0);
                    //rect(i, counter+1, 1, 1);
                    pixels[(i+1)*w*3 + (j+0)*3 + 0] = (unsigned char) 0;
                    pixels[(i+1)*w*3 + (j+0)*3 + 1] = (unsigned char) 0;
                    pixels[(i+1)*w*3 + (j+0)*3 + 2] = (unsigned char) 0;
                }
                else if (pixel1== 255 && pixel2== 125) { // OK
                    //fill(125);
                    //rect(i+1, counter+1, 1, 1);
                    pixels[(i+1)*w*3 + (j+1)*3 + 0] = (unsigned char) 125;
                    pixels[(i+1)*w*3 + (j+1)*3 + 1] = (unsigned char) 125;
                    pixels[(i+1)*w*3 + (j+1)*3 + 2] = (unsigned char) 125;
                }
            }
    
        
    }
    
    // copies pixel into output image
    output.setFromPixels( pixels, w, h, OF_IMAGE_COLOR );
}


//--------------------------------------------------------------
void CellularAutomataOfxApp::touchUp(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void CellularAutomataOfxApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void CellularAutomataOfxApp::touchCancelled(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void CellularAutomataOfxApp::lostFocus(){
    
}

//--------------------------------------------------------------
void CellularAutomataOfxApp::gotFocus(){
    
}

//--------------------------------------------------------------
void CellularAutomataOfxApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void CellularAutomataOfxApp::deviceOrientationChanged(int newOrientation){
    
}
