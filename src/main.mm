#include "ofMain.h"
#include "CellularAutomataOfxApp.h"
#include "ofxiPhoneExtras.h"

int main(){
	//ofSetupOpenGL(1024,768, OF_FULLSCREEN);			// <-------- setup the GL context

	ofAppiPhoneWindow * iOSWindow = new ofAppiPhoneWindow();
	
	//iOSWindow->enableDepthBuffer();
	//iOSWindow->enableAntiAliasing(4);
	
	iOSWindow->enableRetinaSupport();
	
	ofSetupOpenGL(iOSWindow, 1536, 2048, OF_FULLSCREEN);
	ofRunApp(new CellularAutomataOfxApp);
}
