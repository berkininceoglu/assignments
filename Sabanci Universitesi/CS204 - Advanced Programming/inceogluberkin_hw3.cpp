#include <iostream>
#include <string>
#include <fstream>
#include "DynIntStack.h"

using namespace std;

//Berkin Inceoglu 23641 
//2018 Summer term CS204 Homework 3 – The Hard Way


void beginning(ifstream & input,ifstream & input2, string & choice);//ask for file names and the printing order
void pushing (ifstream & input , ifstream & input2, string choice, DynIntStack & stk1, DynIntStack & stk2);//pushes words to stacks from files
void reverse(DynIntStack & file, DynIntStack & file3, DynIntStack & file2, DynIntStack & file4);//reverses file to file3 and file2 to file4 in this way it is easier to print first element
void print(string choice, DynIntStack & file3, DynIntStack & file4);//print mutual words in both files with their occurences


int main()
{
	ifstream input, input2;
	string choice;
	DynIntStack file, file2, file3, file4;

	beginning(input,input2, choice);

	pushing (input, input2, choice, file, file2);

	reverse(file, file3, file2, file4);

	print (choice, file3, file4);

	return 0;
}

void beginning (ifstream & input,ifstream & input2, string & choice)
{
	string file, file2;


	cout << "This program finds the common words of two files using stacks.\n---\n";
	cout << "Enter the first file name: ";
	cin >> file;
	input.open(file.c_str());
	while (input.fail())//ask untils the right file name entered
	{
		cout << "Enter the first file name: ";
		cin >> file;
		input.open(file.c_str());
	}
	cout << "Enter the second file name: ";
	cin >> file2;
	input2.open(file2.c_str());
	while (input2.fail()) //ask untils the right file name entered
	{
		cout << "Enter the second file name: ";
		cin >> file2;
		input2.open(file2.c_str());
	}
	cout << "Choose with respect to which file the result will be sorted to (1: first file, 2: second file): ";
	cin >> choice;
	while (choice != "1" && choice != "2") // it repeats asking until the choice is either string 1 or 2
	{
		cout << "---\nInvalid choice\n---\n";
		cout << "Choose with respect to which file the result will be sorted to (1: first file, 2: second file): ";
		cin >> choice;
	}
	cout <<"---\n";
}

void pushing (ifstream & input , ifstream & input2, string choice, DynIntStack & stk1, DynIntStack & stk2)
{
	DynIntStack copyA, copyB, copyC;
	string word, word2;

	while (input >> word)//takes words from file
	{
		bool found=false;
		int count =0;
		count++;
		copyB.push(word, count);//pushes all words to stack
		DynIntStack copyA(copyC);
		while(!copyA.isEmpty())
		{
			string name;
			int num;
			copyA.pop(name, num);//checks is it pushed before
			if (name == word)
			{
				found =true;
			}
		}
		if(found != true)
			copyC.push(word, count); //it pushes a word only once

	}
	DynIntStack copyD(copyC);
	while(!copyD.isEmpty())
	{
		DynIntStack copyE(copyB); //deep copies are constructed to preserve the original one
		int count =0;
		string name;
		int num;
		copyD.pop(name,num);
		while(!copyE.isEmpty())
		{
			string name2;
			int num2;
			copyE.pop(name2,num2); // it is implemented to count occurence of a word
			if (name == name2)
				count++;
		}
		stk1.push(name, count); //final stack within words and their occurences

	}

	DynIntStack  copy1, copy2, copy3; //same process for second file
	while (input2 >> word2)
	{

		bool found=false;
		int count =0;
		count++;
		copy2.push(word2, count);
		DynIntStack copy1(copy3);
		while(!copy1.isEmpty())
		{
			string name;
			int num;
			copy1.pop(name, num);
			if (name == word2)
			{
				found =true;
			}

		}
		if(found != true)
			copy3.push(word2, count);
	}

	DynIntStack copy4(copy3);
	while(!copy4.isEmpty())
	{
		DynIntStack copy5(copy2);
		int count =0;
		string name;
		int num;
		copy4.pop(name,num);
		while(!copy5.isEmpty())
		{
			string name2;
			int num2;
			copy5.pop(name2,num2);
			if (name == name2)
				count++;
		}
		stk2.push(name, count);
	}
}

void reverse(DynIntStack & file, DynIntStack & file3, DynIntStack & file2, DynIntStack & file4)
{
	while(!file.isEmpty()) // it takes from a stack and pushes to another stack to make new stack in upside down order 
	{
		string word;
		int num;
		file.pop(word, num);
		file3.push(word, num);
	}
	while(!file2.isEmpty())
	{
		string word;
		int num;
		file2.pop(word, num);
		file4.push(word, num);
	}
}

void print(string choice, DynIntStack & file3, DynIntStack & file4)
{
	DynIntStack copy(file3);
	DynIntStack copy2(file4);
	DynIntStack final;

	if (choice == "1") // string choice decided how stacks are going to be printed if choice is 1 then it is going to be printed in an order that is in file 1
	{
		while(!copy.isEmpty())
		{
			string word;
			int num, max;
			copy.pop(word,num);
			DynIntStack copy2(file4);
			while(!copy2.isEmpty())
			{
				string word2;
				int num2;
				copy2.pop(word2, num2);
				if(num > num2)
					max =num2;
				else if (num < num2)
					max =num;
				else
					max=num;

				if(word == word2)
				{
					final.push(word,max);
				}

			}

		}
	}
	else if (choice == "2")
	{
		while(!copy2.isEmpty())
		{
			string word;
			int num, max;
			copy2.pop(word,num);
			DynIntStack kopya(file3);
			while(!kopya.isEmpty())
			{
				string word2;
				int num2;
				kopya.pop(word2, num2);
				if(num > num2) // it selects minimum occurence to print
					max =num2;
				else if (num < num2)
					max =num;
				else
					max=num;

				if(word == word2)
				{
					final.push(word,max); //pushed word with its occurence
				}

			}

		}
	}

	while (!final.isEmpty()) // printing operation starts until stack got empty
	{
		string word;
		int num;
		final.pop(word, num);
		cout << "The word \"" << word << "\" occurred at least " << num << " time(s) in both files.\n";
	}
}