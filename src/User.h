#pragma once
#include "QAdata.h"
#include "ofApp.h"

//1st user Intialiser will be tackled in a different code
//index is an object with two lists of question
//write a code for path allocation

const int len = 5;

class User// holds the data of each user who interacts with the installation
	{
		//questionask Questions to be asked to the user  //from earlier user                            question/ recorded/verified /(index a)/1,1
		//giveanswer  Answers the user gives to the question asked by the earlier user/ developing/     answer/ recording/verified /(index a)/0,0
		//askquestion  Question asked by the user/                                                      question/ recording / verify / (index b)/1,0
		//answergive  Answer to the questions to be asked by the user (index b) /from earlier user /      answer/ recorded/verified/(index b)/0,1
	public:

		int type,usernumber; //question index 0=a, 1=b; //count is the user number for file saving purposes
		QAdata questionask[len], giveanswer[len], askquestion[len], answergive[len]; //_Debug phase _ using number instead of variable

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
			usernumber = number;
		
			if (temp.type == 0)
				type = 1;
			else type = 0;

			for (int i = 0; i<len; i++)
			{
				questionask[i] = temp.askquestion[i];
				answergive[i] = temp.giveanswer[i];
				askquestion[i].text = index[type].qa[i];//intialises question of type from the index
				askquestion[i].path = ofToString(usernumber) + "_askquestion.mp4";// write code here for path allocation
				giveanswer[i].verification = 1;
				giveanswer[i].path = ofToString(usernumber) + "_giveanswer.mp4";// write code here for path allocation

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
		cout << "Running_user_" << usernumber << endl;
		for (int i = 0; i<len && ofGetKeyPressed() != 'e'; i++) //if e is pressed the program exits
		{	
			flagqanumber = i; //sends question number to the voice recognition code
			while (ofGetKeyPressed() != 'c') { cout << "getquestion" << endl; };
			questionask[i].play();
			while (ofGetKeyPressed() != 'c') { cout << "reply" << endl; }; //wait till c is pressed //arduino wait
			giveanswer[i].record();
			while (ofGetKeyPressed() != 'c') { cout << "ask" << endl; }; //wait till c is pressed //arduino wait //prompt
			askquestion[i].record();
			while (ofGetKeyPressed() != 'c') { cout << "getreply" << endl; }; //wait till c is pressed //arduino wait //prompt
			answergive[i].play();
		}
	}
	

	};

