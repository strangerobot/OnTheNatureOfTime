#pragma once
#include "QAdata.h"
#include "ofApp.h"

//1st user Intialiser will be tackled in a different code
//index is an object with two lists of question
//write a code for path allocation



class User// holds the data of each user who interacts with the installation
	{
		//questionask Questions to be asked to the user  //from earlier user                            question/ recorded/verified /(index a)/1,1
		//giveanswer  Answers the user gives to the question asked by the earlier user/ developing/     answer/ recording/verified /(index a)/0,0
		//askquestion  Question asked by the user/                                                      question/ recording / verify / (index b)/1,0
		//answergive  Answer to the questions to be asked by the user (index b) /from earlier user /      answer/ recorded/verified/(index b)/0,1

	public:

		int type,usernumber; //question index 0=a, 1=b; //count is the user number for file saving purposes
		QAdata questionask[5], giveanswer[5], askquestion[5], answergive[5];//_Debug phase _ using number instead of variable
		ofVideoGrabber vidGrabber;
		
		struct Index {
			string qa[5];
		}index[2];

		//constructors

	User()
		{		
			
		cout << "Empty User Intialised" << endl;
		/*	for (int i = 0; i<len; i++)
			{
				askquestion[i] = //
			}
		*/

		}

/*	User(int x)
		{
			type = x;
			if (type == 0)
			{
				for (int i = 0; i<len; i++)
				{
					askquestion[i]>text = indexA[i]>text;
				}
			}
			else
				if (type != 0)
				{
					for (int i = 0; i<len; i++)
					{
						askquestion[i]>text = indexB[i]>text;
					}
				}
		} 
*/

	//<below> copies data from previous user and intializes question and paths for the new user
	void Switch(User &temp, int number) //constructor to switch to temp
		{
			intialiseindex();
			usernumber = number;
			int typeset=type;
			if (temp.type == 0)
				type = 1;
			else type = 0;

			for (int i = 0; i<len; i++)
			{
				questionask[i] = temp.askquestion[i];
				answergive[i] = temp.giveanswer[i];
				askquestion[i].text = index[type].qa[i]; //intialises question of type from the index
				askquestion[i].path = ofToString(usernumber) + "_askquestion_" + ofToString(i);
				askquestion[i].verification = 0;// write code here for path allocation
				giveanswer[i].verification = 1; //this function gets the question the user is supposed to answer and puts it into the text container
				giveanswer[i].path = ofToString(usernumber) + "_giveanswer_"+ ofToString(i);// write code here for path allocation
				giveanswer[i].text =index[typeset].qa[i];
				//temp.askquestion[i].data=0;
				//temp.giveanswer[i].data=0;

				//spmething for path too
				cout << "swithch_index_" << i << endl;
			}
			cout << "user_" << usernumber << "_initialised "<< endl;

		} 

	//<below> Runs the current user
	void run()
	{	
		startloop("waiting.mp4");
		globaltextheading = "Sitdown on the chair";
		globaltextbody = "Focus at the circle \nand press a key to intialize";
		wait();//intialiser
		recordloop(); //when key is pressed it just records a few second long clip
		globaltextheading = "Intialiazing...";
		globaltextbody = "Please be patient";
		playtransition(); //fancyvisual
		startloop(ofToString(usernumber-1)+".mp4");
		globaltextheading = "Connected";
		globaltextbody = " ";
		cout << "Running_user_" << usernumber << endl;
		for (int i = 0; i<5 && ofGetKeyPressed() != 'e'; i++) //if e is pressed the program exits
		{	
			flagqanumber = i; //sends question number to the voice recognition code
			////while (ofGetKeyPressed() != 'c') { cout << "getquestion" << endl; };
			cout << "01.getquestion" << endl;
			questionask[i].play();
			////while (ofGetKeyPressed() != 'c') { cout << "reply" << endl; }; //wait till c is pressed //arduino wait
			cout << "02.reply" << endl;
			giveanswer[i].record(false);
			////while (ofGetKeyPressed() != 'c') { cout << "ask" << endl; }; //wait till c is pressed //arduino wait //prompt
			cout << "03.ask" << endl;
			askquestion[i].record(true);
			////while (ofGetKeyPressed() != 'c') { cout << "getreply" << endl; }; //wait till c is pressed //arduino wait //prompt
			cout << "04.getreply" << endl;
			answergive[i].play();
			cout << "cycle_" <<i<<"_done" << endl;
		}
		playtransition2(); //disconnected
	}

	void intialiseindex() {

		index[0].qa[0] = " hello who is this";
		index[0].qa[1] = " are you recorded";
		index[0].qa[2] = " are you from the future";
		index[0].qa[3] = " are you scripted";
		index[0].qa[4] = " are you human";

		index[1].qa[0] = " who are you";
		index[1].qa[1] = " are you real";
		index[1].qa[2] = " are you from the past";
		index[1].qa[3] = " are you free";
		index[1].qa[4] = " are you machine";

	}

	void startloop(string path)
	{
		globallooppath = path;
		cout << "playingloop_" << globallooppath << endl;
	}
	

	void recordloop()
	{
		vidGrabber.setDesiredFrameRate(30);
		vidGrabber.initGrabber(1280, 720);

		for (int i = 0; i<10; i++) //safety
			vidGrabber.update();

		startrecording();
		for (int i=0;i<20;i++)
		{
			ofSleepMillis(33.33);
			vidGrabber.update();
			if (vidGrabber.isFrameNew() && bRecording && i>5) { //so that the intial clicking action of user doesnt get recorded
				bool success = vidRecorder.addFrame(vidGrabber.getPixelsRef());
				if (!success) {
					ofLogWarning("This frame was not added!");
				}
			}
		}

		stoprecording();
		vidGrabber.close();
	}

	void startrecording()
	{
		bRecording = !bRecording;
		if (bRecording && !vidRecorder.isInitialized()) {
			vidRecorder.setup(ofToString(usernumber), vidGrabber.getWidth(), vidGrabber.getHeight(), 30, sampleRate, channels);
			vidRecorder.start();
		}
	}

	void stoprecording()
	{
		bRecording = false;
		vidRecorder.close();
		cout << ">stopping recording" << endl;
	}

	void playtransition()
	{
		globalpath = "intializing.mp4";
	
		playcheck = true;
		while (playcheck == true)
		{
			cout << "";
		}
		cout << "_______________________Out of loop \n";

	}

	void playtransition2()
	{
		globalpath = "closing.mp4";

		playcheck = true;
		while (playcheck == true)
		{
			cout << "";
		}
		cout << "_______________________Out of loop \n";

	}

	void wait()
	{
		while (key == 0)
		{
			cout << ""; //for some reason it unfreezes the code
		}
	}



	};


