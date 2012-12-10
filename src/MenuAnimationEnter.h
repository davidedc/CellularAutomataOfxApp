#pragma once

#include "ofxState.h"
#include "SharedData.h"

class MenuAnimationEnter : public Apex::ofxState<SharedData>
{
public:
	void setup();
	void update();
	void draw();
	string getName();
    ofImage backGroundImage;
    int frameNumberAtStartOfAnimation = 0;
};
