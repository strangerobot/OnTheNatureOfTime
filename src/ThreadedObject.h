#pragma once


#include "ofThread.h"
#include "ofMain.h"
#include "globals.h"


/// This is a simple example of a ThreadedObject created by extending ofThread.
/// It contains data (count) that will be accessed from within and outside the
/// thread and demonstrates several of the data protection mechanisms (aka
/// mutexes).
class ThreadedObject : public ofThread
{

public:

	int usercount = 1;
	User current;
	/// Create a ThreadedObject and initialize the member
	/// variable in an initialization list.
	/// Start the thread.
	void start()
	{	
		User sample;
		setupsample(sample);
		cout << "00_sample test" << sample.giveanswer[0].path << endl;
		current.Switch(sample, usercount);
		cout << "01_user test" << current.answergive[0].path << endl;
		// Mutex blocking is set to true by default
		// It is rare that one would want to use startThread(false).

		startThread();
	}

	/// Signal the thread to stop.  After calling this method,
	/// isThreadRunning() will return false and the while loop will stop
	/// next time it has the chance to.
	void stop()
	{
		stopThread();
	}

	/// Our implementation of threadedFunction.
	void threadedFunction()
	{
		while (isThreadRunning())
		{

			if (usercount < 20) // for testing purpose
			{
				current.run();
				usercount++;
				User temp = current;
				current.Switch(temp, usercount);
			}
		}
	}

	void setupsample(User &sample) {

		sample.type = 0;
		for (int i = 0; i < 5; i++)
		{
			sample.askquestion[i].verification = 1;
			sample.giveanswer[i].path = "0_giveanswer_" + ofToString(i);
			sample.askquestion[i].path = "0_askquestion_" + ofToString(i);
			cout << sample.askquestion[i].path << endl;
		}
		cout << "____sample intialised____" << endl;
	}

	void draw()
	{
		
	
	}


	
};
