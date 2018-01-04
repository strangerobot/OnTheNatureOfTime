#pragma once

#include "ofMain.h"
#include "User.h"
#include "QAdata.h"
#include <stdio.h>
#include "ofxVideoRecorder.h"

#include "ofxLibwebsockets.h"
#define NUM_MESSAGES 30

class Index {
public:
	string qa[5];
};


const int len = 1;
int flagquestion = 0,flagqanumber=0; //global flag which is used to see if it needs to listen to the incoming stream of voice // flag for QA number to be used for veryfying the question asked
float tolerance = 90.0; //tolerance for voice recognition

//below_parameters for video recording
bool bRecording=false; //checks if recording is on or not
int sampleRate=44100;
int channels=2;
ofVideoGrabber   vidGrabber;
ofxVideoRecorder  vidRecorder;
ofSoundStream      soundStream;
ofFbo recordFbo;
ofPixels recordPixels;

Index index[2];


//below class definition for qa index

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
		void intialiseindex();

	
		
		ofxLibwebsockets::Server server;

		bool bSetup;


		// websocket methods
		void onConnect(ofxLibwebsockets::Event& args);
		void onOpen(ofxLibwebsockets::Event& args);
		void onClose(ofxLibwebsockets::Event& args);
		void onIdle(ofxLibwebsockets::Event& args);
		void onMessage(ofxLibwebsockets::Event& args);
		void onBroadcast(ofxLibwebsockets::Event& args);
		//recorder//
		void audioIn(float * input, int bufferSize, int nChannels);

		int usercount = 1; //keeps track of the user number in draw



		////////////dontknowhowtoimplementityet
		User current;

};
