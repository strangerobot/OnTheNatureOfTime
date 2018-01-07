#pragma once
#include "ofApp.h"

bool bRecording = false; //checks if recording is on or not
int sampleRate = 44100;
int channels = 2;
const int len = 5;
int flagquestion = 0, flagqanumber = 0;
float tolerance = 60.0;

ofVideoGrabber vidGrabber;
ofxVideoRecorder vidRecorder;
ofSoundStream   soundStream;
ofFbo  recordFbo;
ofPixels recordPixels;

//--------------------------------------------------------------
void ofApp::setup(){

	
	User sample;
	
	ofxLibwebsockets::ServerOptions options = ofxLibwebsockets::defaultServerOptions();
	options.port = 9092;
	options.bUseSSL = false; // you'll have to manually accept this self-signed cert if 'true'!
	bSetup = server.setup(options);

	// this adds your app as a listener for the server
	server.addListener(this);


	/// parts from video recorder
	sampleRate = 44100;
	channels = 2;

	ofSetFrameRate(60);
	//ofSetLogLevel(OF_LOG_VERBOSE);
	vidGrabber.setDesiredFrameRate(30);
	vidGrabber.initGrabber(640, 480);
#ifdef TARGET_WIN32
	vidRecorder.setFfmpegLocation("ffmpeg"); // use this is you have ffmpeg installed in your data folder
#endif

					  // override the default codecs if you like
					  // run 'ffmpeg -codecs' to find out what your implementation supports (or -formats on some older versions)
	vidRecorder.setVideoCodec("mpeg4");
	vidRecorder.setVideoBitrate("800k");
	vidRecorder.setAudioCodec("mp3");
	vidRecorder.setAudioBitrate("192k");
	soundStream.setup(this, 0, channels, sampleRate, 256, 1);
	ofSetWindowShape(vidGrabber.getWidth(), vidGrabber.getHeight());
	bRecording = false;
	ofEnableAlphaBlending();

	///start the server
	cout << "____sleep";
	ofSleepMillis(1000);
	string url = "http";
	if (server.usingSSL()) {
		url += "s";
	}
	url += "://localhost:" + ofToString(server.getPort());
	ofLaunchBrowser(url);
	///



	 //follow below
	//loadthe sample user
	setupsample(sample);
	cout<<"00_sample test"<< sample.giveanswer[0].path << endl;
	current.Switch(sample, usercount );
	usercount++;
	cout <<"01_user test"<< current.answergive[0].path<<endl;
}

//--------------------------------------------------------------
void ofApp::update(){

	vidGrabber.update();
	if (vidGrabber.isFrameNew() && bRecording) {
		bool success = vidRecorder.addFrame(vidGrabber.getPixelsRef());
		if (!success) {
			ofLogWarning("This frame was not added!");
		}
	}

}

void ofApp::audioIn(float *input, int bufferSize, int nChannels) {
	if (bRecording)
		vidRecorder.addAudioSamples(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(255, 255, 255);
	vidGrabber.draw(0, 0);
	if (usercount < 1) // for testing purpose
	{
		current.run();
		usercount++;
		User temp = current;
		current.Switch(temp, usercount);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){



}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::onConnect(ofxLibwebsockets::Event& args) {
	cout << "on connected" << endl;
}

//--------------------------------------------------------------
void ofApp::onOpen(ofxLibwebsockets::Event& args) {
	cout << "new connection open" << endl;
}

//--------------------------------------------------------------
void ofApp::onClose(ofxLibwebsockets::Event& args) {
	cout << "close" << endl;
}

//--------------------------------------------------------------
void ofApp::onIdle(ofxLibwebsockets::Event& args) {
	cout << "idle" << endl;
}

void ofApp::onMessage(ofxLibwebsockets::Event& args) {
	cout << "message " << args.message << endl;
	if (flagquestion == 1)
	{
		cout << "[?] Verification for __|" <<args.message<< "|___against___|" << current.askquestion[flagqanumber].text<<"|"<< endl;
		current.askquestion[flagqanumber].checkverify(args.message);
	}//runs the verification function in the current users current askquestion
}




void ofApp::setupsample( User &sample) {

	sample.type = 0;
	for (int i = 0;i < 5;i++)
	{
		sample.askquestion[i].verification = 1;
		sample.askquestion[i].path = "sample_askquestion_" + ofToString(i);
		sample.giveanswer[i].path = "sample_giveanswer_" + ofToString(i);
		cout << sample.askquestion[i].path << endl;
	}
	cout << "____sample intialised____" << endl;
}