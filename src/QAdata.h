#pragma once
#include "ofMain.h"

class QAdata
{

public:
			//int question; //checks wether the object is a question(1) or an answer(2)
			//int data; //checks wether the object already had data or not
		int verification; //Checks wether the file is verified or not
		string text = " "; //Collects the on screen text
		string path; //path of file
		

		void record()// function that triggers recording
		{
			flagquestion = 1;

		}

		void play()
		{
		}

		void checkverify(string voice)
		{
			
			if (StringCompare(voice, text) > tolerance)
			{
				verification = 1;
				flagquestion = 0; //if the correct answer is achieved, the program stops listening or else continues
			}
			else verification = 0;
			//make verification 1 if it passes the test
		}


		//below, copied function which retursn similarity index of two strings
		static double StringCompare(string a, string b) 
		{
			if (a == b) //Same string, no iteration needed.
				return 100;
			if ((a.length == 0) || (b.length == 0)) //One is empty, second is not
			{
				return 0;
			}
			double maxLen = a.length > b.length ? a.length : b.length;
			int minLen = a.length < b.length ? a.length : b.length;
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
