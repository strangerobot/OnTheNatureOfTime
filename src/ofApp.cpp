#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	intialiseindex(); //setup the two question sets


	// setup a server with default options on port 9092
	// - pass in true after port to set up with SSL
	//bSetup = server.setup( 9093 );
	

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
	ofSetLogLevel(OF_LOG_VERBOSE);
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
	string url = "http";
	if (server.usingSSL()) {
		url += "s";
	}
	url += "://localhost:" + ofToString(server.getPort());
	ofLaunchBrowser(url);
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
	if(flagquestion==1)
	_currentuser.askquestion[flagqanumber].checkverify(args.message); //runs the verification function in the current users current askquestion
}


void ofApp::intialiseindex() {

	index[0].qa[0] = "";
	index[0].qa[1] = "";
	index[0].qa[2] = "";
	index[0].qa[3] = "";
	index[0].qa[4] = "";

	index[1].qa[0] = "";
	index[1].qa[1] = "";
	index[1].qa[2] = "";
	index[1].qa[3] = "";
	index[1].qa[4] = "";

}