#include <iostream>
#include "strutils.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	ifstream program;
	ifstream coupon;
	ifstream scores;

	string programName;
	string couponName;
	string matchScores;

	string word;
	string otherWord;
	string s;
	string alex;
	int i=0;

	cout << "This is a simple betting program." <<endl<<endl;
	cout << "Please enter a filename which contains whole betting program: ";
	cin>> programName;
	
	program.open(programName.c_str());
	if (program.fail())
	{
		cout << "Error for opening " << programName << " Please enter filename again: ";
		cin>> programName;
	}

	cout << "Please enter a filename which contains the matches played by a user: ";
	cin>> couponName;

	coupon.open(couponName.c_str());
	if (coupon.fail())
	{
		cout << "Error for opening " << couponName << " Please enter filename again:";
		cin>> couponName;
	}
	cout << "Please enter a filename which contains the match scores of the week: ";
	cin>> matchScores;

	scores.open(matchScores.c_str());
	if (scores.fail())
	{
		cout << "Error for opening " << matchScores << " Please enter filename again: ";
		cin>> matchScores;
	}

	cout << "\n";

	while(program >> word)
	{
		while(coupon >> otherWord)
		{

			if (otherWord == word )
			{
				cout<< otherWord;
			getline(program, s); 
			cout << s << endl;
				
			}


		}
		coupon.clear();
		coupon.seekg(0);
	}


	cout << "\n !!! BET \"LEGALLY\" AND \"RESPONSIBLY\" !!!"<<endl;
	return 0;
}