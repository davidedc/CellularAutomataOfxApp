Start of the project
======
Ben, Pat, Tim and I will give it a go at making an app. In my case, I'll do something simple - an app that generates some art via cellular automata. I've done some similar basic sketches in sketchpatch, which look pretty, so I thought to give it a go... I'm only going to do this a couple of hours every week, so it will be slow, but hopefully steady.


Week 1
-------
Week one I ported an algorithm that draws a conservative Cellular Automaton. I ported it over from a sketchPatch sketch that I did in the past. The first observation is that the pixmap for an iPad retina display is around 10Mb. It's a huge texture to send to the GPU. For the time being it will be fine, but right now on an iPad 3 it can only refresh the screen 2 times per second.

<img src="https://github.com/davidedc/CellularAutomataOfxApp/raw/master/someImagesOfTheApp/CellularAutomataOfxApp-img-1.PNG" width="851" >

Week 2
-------
Week two I started playing with some designs of what the splash screen and the first screen of the app might look like. I've drafted something simple based on simple typography. And so from the designs I made a splash screen for all devices, and made the code that calculated the pixmap resolution-independent.

Code-wise, I'm now drawing the menu text on a gray semitransparent box. I had to figure out a way to make the background container box to fit harmoniously around the text, which took some fiddling around the margin sizes. One would think that just adding a few pixels to the top/bottom/left/right of the text bounding box would be fine, but it turns out that the descenders and the difference in height between the capital letters and the normal letters play all kinds of optical tricks, so some adjustments are needed.

Also I added a very simple state machine to manage the couple of different states so far (start/menu/drawing the CA animation) - I used Neil Mendoza's state machine code from https://github.com/neilmendoza/ofxStateMachine.

So, now there is a nice splash screen, a very simple menu page, and by tappig the animation of Cellular Automata starts. Tapping again brings back to the menu screen. The refresh rate is stil very slow though, I didn't address that yet.

Something simple, but it's beginning to take some sort of shape.

<img src="https://raw.github.com/davidedc/CellularAutomataOfxApp/master/designs/splash%20screens/iPad2SplashScreenV1.png" width="851" >

