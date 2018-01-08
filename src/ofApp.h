#pragma once

#include "ofMain.h"
#include "User.h"
#include "QAdata.h"
#include <stdio.h>
#include "ofxVideoRecorder.h"
#include "ofxLibwebsockets.h"
#include "globals.h"
#include "ThreadedObject.h"

#define NUM_MESSAGES 30





class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();

	
		
		ofxLibwebsockets::Server server;

		bool bSetup;


		// websocket methods
		void onConnect(ofxLibwebsockets::Event& args);
		void onOpen(ofxLibwebsockets::Event& args);
		void onClose(ofxLibwebsockets::Event& args);
		void onIdle(ofxLibwebsockets::Event& args);
		void onMessage(ofxLibwebsockets::Event& args);
		void onBroadcast(ofxLibwebsockets::Event& args);


		bool playvideo(string path);
		
		//recorder//
		void audioIn(float * input, int bufferSize, int nChannels);

		
		//keeps track of the user number in draw
		 //sets up the first sample user
		ofVideoPlayer player;
		ThreadedObject threadobj;


};
