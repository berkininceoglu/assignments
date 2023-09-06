#include <iostream>
#include <string>
#include "strutils.h"

//Berkin Inceoglu 23641 

using namespace std;

bool stop (string exp) // this bool checks does user want to end this program)
{
	if(exp == ("EXIT"))
	{
		return false;
	}
	else if (exp == ("exit")){
		return false;
	}
	else if (exp == ("QUIT")){
		return false;
	}
	else if (exp == ("quit")){
		return false;
	}
	else if (exp == ("END")){
		return false;
	}
	else if (exp == ("end")){
		return false;
	}
	else 
		return true;
}

bool check (string exp, int indexMinus, int indexPlus, int indexDiv, int indexLet)
{ // Invalid inpust gets into this bool and it shows message that entry is invalid
	if(indexMinus == 0 || indexPlus == 0) // it looks that does line start with (-) or (+)
	{
		cout<<"Invalid entry"<<endl<<endl;
		return false;
	}
	else if(indexMinus == exp.length()-1 || indexPlus == exp.length()-1)// it looks that does line end with (-) or (+)
	{
		cout<<"Invalid entry"<<endl<<endl;
		return false;
	}
	else if (exp.substr(indexMinus+1, 1) == "-" ||exp.substr(indexPlus+1, 1) == "+")//it is for consecutive operators like "++"
	{
		cout<<"Invalid entry"<<endl<<endl;
		return false;
	}
	else if (exp.substr(indexDiv+1, 1) == "0" && exp.length() > 1 ) // Controls is there a 0 after a divisor
	{
		cout<< "You cannot divide by 0"<<endl<<endl;
		return false;
	}
	else if (indexLet >= 0 ) // Just checks for a in sample run could be multiplied to all letters
	{
		cout<<"Invalid entry"<<endl<<endl;
		return false;
	}
	else
		return true;
}


int main()
{
	while(true) // main while 
	{
		string exp, number;
		int indexPlus, indexMinus, length, indexMultip, indexDiv,indexLet;
		double sum, num=0, min;

		do //
		{
			cout << "Please enter the expression to calculate: ";
			cin >> exp; 

			length = exp.length(); // all operators' and a letter's first occurence are calculated here
			indexMultip = exp.find("*");
			indexDiv = exp.find("/");
			indexPlus = exp.find("+");
			indexMinus = exp.find("-");
			indexLet = exp.find("A");
		}
		while(check(exp, indexMinus, indexPlus, indexDiv, indexLet) == false);


		if (stop(exp) == false) // ending bool
		{
			cout<< "GOOD BYE"<<endl;
			return 0;
		}
		min = indexPlus, indexMultip; // my code operates right hand side of the operator

		if (indexMinus < min)         // so it is needed to get number which is on left 
		{
			int min = indexMinus;     // of first operator. this structure determines
		}
		else if (indexDiv < min)     // first operator and the number on left of it
		{
			int min = indexDiv;
		}

		string beginning= exp.substr(0, min);
		double sum1 = atof(beginning);      //converts into number which was on the left
		sum = sum1;

		while (indexPlus != string::npos)   // if there is a + sign
		{   
			number = exp.substr(indexPlus, length); // takes string after first operator
			num = atoi(number);  // converts string into number until next operator
			sum = sum + num;     // add num to sum which was first number was on the left
			indexPlus = exp.find("+", indexPlus+1); // then finds another + sign and repeat
		}

		while (indexMinus != string::npos)  //same as plus sign
		{   
			number = exp.substr(indexMinus+1, length);
			num = atoi(number);    
			sum = sum - num;
			indexMinus = exp.find("-", indexMinus+1);
		}

		while (indexMultip != string::npos)  //same as plus sign
		{   
			number = exp.substr(indexMultip+1, length);
			num = atof(number);
			sum = sum * num;
			indexMultip = exp.find("*", indexMultip+1);
		}

		while (indexDiv != string::npos) //same as plus sign
		{   
			number = exp.substr(indexDiv+1, length);
			num = atof(number);
			sum = sum / num;
			indexDiv = exp.find("/", indexDiv+1);
		}
		cout<< sum << endl<<endl; //shows summation of all numbers in string
	}
	return 0;
}