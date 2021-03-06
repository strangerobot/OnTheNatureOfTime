#pragma once
#include "ofMain.h"
#include "ofApp.h"
#include "ofxVideoRecorder.h"
#include "globals.h"
#include <conio.h>


#define DELAY 1000.0



class QAdata
{

public:
			//int question; //checks wether the object is a question(1) or an answer(2)
			//int data; //checks wether the object already had data or not
			//use normal laptop environment with keypressed for testing the code

		int verification; //Checks wether the file is verified or not
		string text = " "; //Collects the on screen text
		string path;//path of file
		string ext=".mp4";
		ofVideoGrabber vidGrabber;


		

		void record( bool question )// function that triggers recording
		{	
			vidGrabber.setDesiredFrameRate(30);
			vidGrabber.initGrabber(1280, 720);
			globaltextbody = text;
			for(int i=0;i<10;i++)
				vidGrabber.update();

			if(question==true)
			{ 
				flagquestion = 1;
				globaltextheading = "Ask ";
				do
				{
					///////cout << "Press the button to record"<<endl; //replace with gui part
					//listen for arduino button press//or normal button press
					cout << " ask question :" << text << endl;


					recordandwait();
					if (verification != 1)
					{
						cout << "wrong question, try again" << endl;
						globaltextheading = "Ask again..";
						verification = 0;
					}

					stoprecording();
				} while (verification != 1);


			}
			if (question == false)
			{	
				globaltextheading = "Reply to";
				recordandwait();
			}

			vidGrabber.close();
		}

		void recordandwait()
		{
			cout << "hold space to start recording" << endl;
			globalrec = "hold space to record";
			while (key == 0)
			{
				cout << ""; //for some reason it unfreezes the code;
			}
			globalrec = "recording";
				startrecording();
				cout << "release space to stop recording__" << key << endl;
				while (key > 0) {
					
					vidGrabber.update();
					if (vidGrabber.isFrameNew() && bRecording) {
						bool success = vidRecorder.addFrame(vidGrabber.getPixelsRef());
						if (!success) {
							ofLogWarning("This frame was not added!");
						}
					}
				}
		
			stoprecording();
			globalrec = " ";
		}


		void startrecording()
		{
			bRecording = !bRecording;
			if (bRecording && !vidRecorder.isInitialized()) {
				vidRecorder.setup(path, vidGrabber.getWidth(), vidGrabber.getHeight(), 30, sampleRate, channels);
				vidRecorder.start();
			}
		cout << ">starting recording_"<<path<<endl;
		}

		void stoprecording()
		{
			bRecording = false;
			vidRecorder.close();
			cout << ">stopping recording"<<endl;
		}

		void play()
		{
			globaltextheading = "Transmitting..";
			globaltextbody = " ";
			globalpath =path+".mp4";
			cout <<"playing___"<<globalpath<<endl;
			
				playcheck = true;
			while(playcheck==true)
			{
				cout <<"";
			}
			cout << "_______________________Out of loop \n";
		
			//use a global var to send the path
			//and something in draw to start playing
		}

		void checkverify(string voice)
		{	

			////////cout << "[?] Verification similarity : " << StringCompare(voice, text) << endl;
			if (StringCompare(voice, text) > tolerance)
			{
				verification = 1;
				flagquestion = 0; //if the correct answer is achieved, the program stops listening or else continues
			}
			else verification = 0;
			//make verification 1 if it passes the test
		}


		//below, copied function which retursn similarity index of two strings
		static double StringCompare(string b,string a) 
		{
			if (a == b) //Same string, no iteration needed.
				return 100;
			if ((a.length() == 0) || (b.length() == 0)) //One is empty, second is not
			{
				return 0;
			}
			double maxLen = a.length() > b.length() ? a.length() : b.length();
			int minLen = a.length() < b.length() ? a.length() : b.length();
			int sameCharAtIndex = 0;
			for (int i = 0; i < minLen; i++) //Compare char by char
			{
				if (a[i] == b[i])
				{
					sameCharAtIndex++;
				}
			}
			return sameCharAtIndex / maxLen * 100;
		}



		void display()
		{

		}



		QAdata()
		{
			//question=1;
			//data=0;
			verification = 0;
			text = " ... ";
		}

		/* public QAdata (int x, int y)
		{
		question=x;
		data=y;
		if (question==0 || data!=0)
		verification=1;
		}
		*/

		QAdata(QAdata &temp)
		{
			//question=temp.question;
			//data=temp.data;
			verification = temp.verification;
			text = temp.text;
			path = temp.path;
			//something to copy path also


		}

	};

