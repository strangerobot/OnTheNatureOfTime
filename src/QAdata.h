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
		char key;
		

		void record( bool question )// function that triggers recording
		{
			
			if(question==true)
			{ 
				flagquestion = 1;
				do
				{
					///////cout << "Press the button to record"<<endl; //replace with gui part
					//listen for arduino button press//or normal button press
					cout << " ask question :" << text << endl;


					cout << "press space to start recording" << endl;
					getch();

					startrecording();

					cout << "press space to stop recording" << endl;
					getch();
					if (verification != 1)
					{
						cout << "wrong question, try again" << endl;
						verification = 0;
					}

					stoprecording();
				} while (verification != 1);
			}

			if (question == false)
			{
				cout << "press space to start recording" << endl;
				getch();
				startrecording();
				cout << "press space to stop recording"<<endl;
				getch();
				stoprecording();
			}


		}

		void startrecording()
		{
			bRecording = !bRecording;
			if (bRecording && !vidRecorder.isInitialized()) {
				vidRecorder.setup(path+ext, vidGrabber.getWidth(), vidGrabber.getHeight(), 30, sampleRate, channels);

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
			//code for playing the correct video once
			cout << ">>>Playing_" <<path << endl;
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

