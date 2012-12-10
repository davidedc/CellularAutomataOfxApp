#include "CellularAutomataOfxApp.h"
#include "AnimateAutomatonState.h"
#include "FirstScreenState.h"
#include "MenuAnimationEnter.h"
//#include "PlayAutomataAnimationState.cpp"
//#include "FirstScreenState.h"


//--------------------------------------------------------------
CellularAutomataOfxApp::CellularAutomataOfxApp(CGSize theSize, bool is_Ipad, bool is_Retina){
    theScreenSize = theSize;
    isIpad = is_Ipad;
    isRetina = is_Retina;
}

//--------------------------------------------------------------
void CellularAutomataOfxApp::setup(){
	//cout <<  "the number is " << setprecision (15) << screenSize.width;
    //ofLog(OF_LOG_NOTICE, "the number is " + ofToString((int)screenSize.width));
    ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_PORTRAIT);

    
    //ofSeedRandom();
    //w = screenSize.width;   // define width of screen
    //h = screenSize.height;  // define height of screen
    
    
	// wishful thinking, this thing is very slow.
    ofSetFrameRate(60);
    
    
    // see this on how to add files as resources:
    // http://stackoverflow.com/questions/10247680/adding-resource-files-to-xcode
    stateMachine.getSharedData().testFont.loadFont("MgOpenModernaRegular.ttf", 80, true, false, false);
    
    // initialise state machine
	stateMachine.addState(new AnimateAutomatonState());
	stateMachine.addState(new FirstScreenState());
	stateMachine.addState(new MenuAnimationEnter());
	stateMachine.changeState("MenuAnimationEnter");
    
    stateMachine.getSharedData().isIpad = isIpad;
    stateMachine.getSharedData().isRetina = isRetina;
    stateMachine.getSharedData().screenHeightPixels = (int)theScreenSize.height;
    stateMachine.getSharedData().screenWidthPixels = (int)theScreenSize.width;
    ofLog(OF_LOG_NOTICE, "screen height: " + ofToString(stateMachine.getSharedData().screenHeightPixels));
    stateMachine.getSharedData().pixels = new unsigned char[(int)(theScreenSize.height*theScreenSize.width*3)];  // pixel array


    ////////////////////////////////////////////
    // initialise the writings of the menu
    ////////////////////////////////////////////
    
    // Put the info from the global state into local variables. We'll put the
    // local variables back into the local state later.
    int marginSize = stateMachine.getSharedData().marginSize;
    int ascender = stateMachine.getSharedData().ascender;
    int upperVerticalMarginSize = stateMachine.getSharedData().upperVerticalMarginSize;
    int totalVerticalMarginSize = stateMachine.getSharedData().totalVerticalMarginSize;
    ofRectangle appTitleStringBoundingBox =  stateMachine.getSharedData().appTitleStringBoundingBox;
    string appTitleString = stateMachine.getSharedData().appTitleString;

    appTitleStringBoundingBox = stateMachine.getSharedData().testFont.getStringBoundingBox(appTitleString, 0,0);
    
    // calculate the horizontal margin size. Note that horizontal margin
    // size is easier than the vertical. Vertical margin size
    // has to deal with the presence of descenders, which skew the
    // perception of vertical centers.
    // Here for the horizontal margin size we simply calculate it
    // as the space that it would take to accommodate an additional "i"
    string appTitleStringWithSideMargins = "i"+appTitleString;
    ofRectangle appTitleStringBoundingBoxWithMargins = stateMachine.getSharedData().testFont.getStringBoundingBox(appTitleStringWithSideMargins, 0,0);
    marginSize = appTitleStringBoundingBoxWithMargins.width - appTitleStringBoundingBox.width;
    
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
    ascender = appTitleStringBoundingBox.height;
    upperVerticalMarginSize = marginSize;
    
    if (appTitleString.find("g")!=string::npos ||
        appTitleString.find("j")!=string::npos ||
        appTitleString.find("q")!=string::npos ||
        appTitleString.find("p")!=string::npos ||
        appTitleString.find("y")!=string::npos
        ) {
        totalVerticalMarginSize = 1.5* marginSize;
        ascender *= 0.77;
    }
    else {
        totalVerticalMarginSize = 2 * marginSize;
        // in theory for this adjustment below one would
        // want to check if the string is all made of caps
        // in which case the full top margin would be applied.
        upperVerticalMarginSize *= 0.8;
    }
    

    // Put the info from the local variables back into the global state.
    stateMachine.getSharedData().marginSize = marginSize;
    stateMachine.getSharedData().ascender = ascender;
    stateMachine.getSharedData().upperVerticalMarginSize = upperVerticalMarginSize;
    stateMachine.getSharedData().totalVerticalMarginSize = totalVerticalMarginSize;
    stateMachine.getSharedData().appTitleStringBoundingBox = appTitleStringBoundingBox;

}

//--------------------------------------------------------------
string CellularAutomataOfxApp::getName() {
	return "startupState";
}

//--------------------------------------------------------------
void CellularAutomataOfxApp::update(){
}

//--------------------------------------------------------------
void CellularAutomataOfxApp::draw(){
    
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
