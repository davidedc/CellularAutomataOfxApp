#include "CellularAutomataOfxApp.h"
//#include "PlayAutomataAnimationState.cpp"
//#include "FirstScreenState.h"


//--------------------------------------------------------------
CellularAutomataOfxApp::CellularAutomataOfxApp(CGSize passed_screenSize){
	screenSize = passed_screenSize;
    
}

//--------------------------------------------------------------
void CellularAutomataOfxApp::setup(){
	//cout <<  "the number is " << setprecision (15) << screenSize.width;
    ofLog(OF_LOG_NOTICE, "the number is " + ofToString((int)screenSize.width));
    ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_PORTRAIT);
    
    
    //ofSeedRandom();
    w = screenSize.width;   // define width of screen
    h = screenSize.height;  // define height of screen
    
    pixels = new unsigned char[w*h*3];  // pixel array
    
	// wishful thinking, this thing is very slow.
    ofSetFrameRate(60);
    
    
    // see this on how to add files as resources:
    // http://stackoverflow.com/questions/10247680/adding-resource-files-to-xcode
	testFont.loadFont("MgOpenModernaRegular.ttf", 80, true, false, false);
    
    //stateMachine.addState(new PlayAutomataAnimationState);
    //stateMachine.addState(new  FirstScreenState);
	//stateMachine.changeState("firstScreen");
    
    
}


//--------------------------------------------------------------
void CellularAutomataOfxApp::update(){
}

//--------------------------------------------------------------
void CellularAutomataOfxApp::draw(){
    ofBackground(0,0,0,255);
    
	ofSetColor(255,255,255);
    calculateBitmap();
    
    // copies pixel into output image
    output.setFromPixels( pixels, w, h, OF_IMAGE_COLOR );
    // draw output image to screen
    output.draw(0,0);
    
    
    
    //enable blending!
	//We are going to use a blend mode that adds
	//all the colors to white.
	ofEnableAlphaBlending();
	//glBlendFunc(GL_ONE, GL_ONE);
    
    string appTitleString = "Digital Forest";
    ofRectangle appTitleStringBoundingBox = testFont.getStringBoundingBox(appTitleString, 0,0);
    
    // calculate the horizontal margin size. Note that horizontal margin
    // size is easier than the vertical. Vertical margin size
    // has to deal with the presence of descenders, which skew the
    // perception of vertical centers.
    // Here for the horizontal margin size we simply calculate it
    // as the space that it would take to accommodate an additional "i"
    string appTitleStringWithSideMargins = "i"+appTitleString;
    ofRectangle appTitleStringBoundingBoxWithMargins = testFont.getStringBoundingBox(appTitleStringWithSideMargins, 0,0);
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
	testFont.drawString(appTitleString, 15, 270);
    
    
    glFlush();
    
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


void CellularAutomataOfxApp:: calculateBitmap() {
    
    ofLog(OF_LOG_NOTICE, "calculating cellular automata pixmap ");
    
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
