#pragma once

#include "ofMain.h"
#include "User.h"
#include "QAdata.h"

#include "ofxLibwebsockets.h"
#define NUM_MESSAGES 30

const int len = 1;



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

		User temp;
		
		ofxLibwebsockets::Server server;

		bool bSetup;

		//queue of rec'd messages
		vector<string> messages;

		//string to send to clients
		string toSend;

		// websocket methods
		void onConnect(ofxLibwebsockets::Event& args);
		void onOpen(ofxLibwebsockets::Event& args);
		void onClose(ofxLibwebsockets::Event& args);
		void onIdle(ofxLibwebsockets::Event& args);
		void onMessage(ofxLibwebsockets::Event& args);
		void onBroadcast(ofxLibwebsockets::Event& args);

};
