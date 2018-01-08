#include "ofVideoGrabber.h"
#include "ofxVideoRecorder.h"

extern const int len;
extern int flagquestion, flagqanumber; //global flag which is used to see if it needs to listen to the incoming stream of voice // flag for QA number to be used for veryfying the question asked
extern float tolerance; //tolerance for voice recognition

						//below_parameters for video recording

extern bool bRecording; //checks if recording is on or not
extern int sampleRate;
extern int channels;

extern ofxVideoRecorder vidRecorder;
extern ofSoundStream   soundStream;
extern ofFbo  recordFbo;
extern ofPixels recordPixels;
extern int key;
extern bool playcheck;
extern string globalpath;

