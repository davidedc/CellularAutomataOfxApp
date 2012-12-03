#include "CellularAutomataOfxApp.h"
#include "AnimateAutomatonState.h"
#include "FirstScreenState.h"
//#include "PlayAutomataAnimationState.cpp"
//#include "FirstScreenState.h"


//--------------------------------------------------------------
CellularAutomataOfxApp::CellularAutomataOfxApp(CGSize theSize){
    theScreenSize = theSize;
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
	stateMachine.changeState("firstScreenState");
    
    stateMachine.getSharedData().screenHeightPixels = (int)theScreenSize.height;
    stateMachine.getSharedData().screenWidthPixels = (int)theScreenSize.width;
    ofLog(OF_LOG_NOTICE, "screen height: " + ofToString(getSharedData().screenHeightPixels));
    stateMachine.getSharedData().pixels = new unsigned char[(int)(theScreenSize.height*theScreenSize.width*3)];  // pixel array


    //stateMachine.addState(new PlayAutomataAnimationState);
    //stateMachine.addState(new  FirstScreenState);
	//stateMachine.changeState("firstScreen");
    
    
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
