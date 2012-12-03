#include "ofMain.h"
#include "CellularAutomataOfxApp.h"
#include "ofxiPhoneExtras.h"
#include "SharedData.h"


int main(){
    
	ofAppiPhoneWindow * iOSWindow = new ofAppiPhoneWindow();
	
	//iOSWindow->enableDepthBuffer();
	//iOSWindow->enableAntiAliasing(4);
	
    //ofLog(OF_LOG_NOTICE, "the number is " + ofAppBaseWindow::getWidth());
    
    // see http://stackoverflow.com/questions/4779221/in-iphone-app-how-to-detect-the-screen-resolution-of-the-device
    // and http://codeatuts.blogspot.co.uk/2012/11/interlude-13-pixels-vs-points-in-ios.html
    // for an explanation of how pixels and points work in iOS.
    // screenBounds below doesn't take into account retina display
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    // you would expect the screenScale to tell you the actual density of the display
    // but not the case. iPad mini has higher ppi than iPad 1 and 2 but it still
    // keeps scale factor of 1.0
    CGFloat screenScale = [[UIScreen mainScreen] scale];
    ofLog(OF_LOG_NOTICE, "scale is " + ofToString(screenScale));
    
    // screenSize below does take into account whether the screen is retina display
    CGSize screenSize = CGSizeMake(screenBounds.size.width * screenScale, screenBounds.size.height * screenScale);
    
    // For the time being we are not making much use of device detection
    // But this would be the way to do it...
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        if (screenScale > 1.0) {
            // isPad Retina
            iOSWindow->enableRetinaSupport();
        }
        else {
            // isIpad 1 or 2 or iPad mini
        }
    }
    else {
        if (screenScale > 1.0) {
            // iPhone Retina
            iOSWindow->enableRetinaSupport();
        }
        else {
            // iPhone
        }
    }
	

	ofSetupOpenGL(iOSWindow, screenSize.width, screenSize.height, OF_FULLSCREEN);
    //glEnable(GL_BLEND);
    //gllBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	ofRunApp(new CellularAutomataOfxApp(screenSize));
}
