#pragma once
#include "ofApp.h"

bool bRecording = false; //checks if recording is on or not
int sampleRate = 44100;
int channels = 2;
const int len = 5;
int flagquestion = 0, flagqanumber = 0;
float tolerance = 60.0;
bool playcheck=false;
string globalpath,globallooppath;
string globaltextheading=" Header ", globaltextbody=" Body ", globalvoiceverif = " ";

ofxVideoRecorder vidRecorder;
ofSoundStream   soundStream;
ofFbo  recordFbo;
ofPixels recordPixels;
int key = 0;

//--------------------------------------------------------------
void ofApp::setup(){
	
	
	
	headertext.loadFont("base.otf", 28);
	bodytext.loadFont("base.otf", 18);
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

#ifdef TARGET_WIN32
	vidRecorder.setFfmpegLocation("ffmpeg"); // use this is you have ffmpeg installed in your data folder
#endif

					  // override the default codecs if you like
					  // run 'ffmpeg -codecs' to find out what your implementation supports (or -formats on some older versions)
	vidRecorder.setVideoCodec("mpeg4");
	vidRecorder.setVideoBitrate("800k");
	vidRecorder.setAudioCodec("pcm_s16le");
	vidRecorder.setAudioBitrate("256k");
	soundStream.setup(this, 0, channels, sampleRate, 256, 1);
	//ofSetWindowShape(vidGrabber.getWidth(), vidGrabber.getHeight());
	bRecording = false;
	ofEnableAlphaBlending();

	///start the server
	cout << "____sleep";
	ofSleepMillis(1000);
	
	if (server.usingSSL()) {
		url += "s";
	}
	url += "://localhost:" + ofToString(server.getPort());
	ofLaunchBrowser(url);
	///

	globallooppath = " ";
	player = new ofVideoPlayer();
	globalpath = "0_askquestion_0.mp4";
	threadobj.start(); //trying to run the service in parallel to the main program
}

//--------------------------------------------------------------
void ofApp::update() {

	if (globalpath != storedpath)
	{
		delete player;
		player = new ofVideoPlayer();
		player->load(globalpath);
		cout << globalpath << endl;
		player->setLoopState(OF_LOOP_NONE);
		player->play();
		storedpath = globalpath;
	}

	if (globallooppath != storedlooppath)
	{
		delete playerloop;
		playerloop = new ofVideoPlayer();
		playerloop->load(globallooppath);
		cout << globallooppath << endl;
		playerloop->setLoopState(OF_LOOP_NORMAL);
		playerloop->play();
		storedlooppath = globallooppath;
	}

	if (player->getIsMovieDone() >= 0.99)
	{
	
		playcheck = false;
		player->stop();
		player->close();
	}


}

void ofApp::audioIn(float *input, int bufferSize, int nChannels) {
	if (bRecording)
		vidRecorder.addAudioSamples(input, bufferSize, nChannels);
} //might need to branchout audio in a different thread

//--------------------------------------------------------------
void ofApp::draw(){
	
	if (playcheck == true )
	{
		player->update();
		player->draw(0, 0, 640, 480);
	}
	else
	{	
		
		playerloop->update();
		playerloop->draw(0, 0, 640, 480);	
	}

	headertext.drawString(globaltextheading, 100, 100);
	bodytext.drawString(globaltextbody, 100, 150);
	bodytext.drawString(globalvoiceverif, 100, 400);
}

void ofApp::exit()
{

	threadobj.stop();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int k){
	key += k;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int k){
	key = 0;
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
	globalvoiceverif = "...";
}

void ofApp::onMessage(ofxLibwebsockets::Event& args) {
	globalvoiceverif = args.message;
	cout << "message " << globalvoiceverif << endl;
	if (flagquestion == 1)
	{	
		
		cout << "[?] Verification for __|" <<args.message<< "|___against___|" << threadobj.current.askquestion[flagqanumber].text<<"|"<< endl;
		threadobj.current.askquestion[flagqanumber].checkverify(args.message);
	}//runs the verification function in the current users current askquestion
}



