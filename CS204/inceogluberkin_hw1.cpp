#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

/*Berkin Inceoglu 23641 
2017-2018 Summer Term CS 204 Homework 1 – Lost for Words 
Basic program that let user play Sunday morning puzzle through .txt files filled with characters.
Words can be found vertically, horizontally, diagonally. Reversed versions of words are okay too.
As a joker inputs that can be found by one character diffence are accepted*/
using namespace std;

void reversing (string & s)
{
	int l = s.length();
	char temp;
	for (int i=0; i<l/2; i++)
	{
		temp = s.at(i);
		s.at(i) = s.at(l-1-i);
		s.at(l-1-i) = temp;
	}
}
void horizontalSearch(int rows, int cols, vector<vector <char> > mat, vector<string> & horizontal)
{
	for (int m=0; m<rows ; m++)////for horizontal searches 
	{
		string hor = "";
		for(int n=0; n<cols ; n++)
		{
			hor += mat[m][n];
		}
		horizontal.push_back(hor);
	}
}
void verticalSearch(int rows, int cols, vector<vector <char> > mat, vector<string> & vertical)
{
	for (int i=0; i<cols ; i++)////for vertical searches 
	{
		string ver = "";
		for(int j=0; j<rows ; j++)
		{
			ver += mat[j][i];
		}
		vertical.push_back(ver);
	}
}
void diagonalSearch(int rows, int cols,int dif, vector<vector <char> > mat, vector<string> & diagonal )
{
	for (int j=0; j<rows-dif; j++)
	{   
		for (int k=0 ; k<cols-dif ; k++)
		{
			string dia="";
			for(int i=0; i+j<rows && i+k<cols; i++)
			{
				dia += mat[i+j][i+k];
			}
			diagonal.push_back(dia);
		}
	}
}
void jokerSearch (string g, string m, string guess, string reversed, vector <string> & joker)
{
	for (int j=0; j<guess.length(); j++)
	{
		g= guess;
		for(int i=0; i<25; i++)
		{
			g.at(j) = 65+i;
			joker.push_back(g);
		}
	}
	for (int j=0; j<reversed.length(); j++)
	{
		m=reversed;
		for(int i=0; i<25; i++)
		{
			m.at(j) = 65+i;
			joker.push_back(m);
		}
	}
}
void findColumn(int cols, int & score, string guess, string reversed, bool & found , vector<string> vertical)
{
	for (int i=0; i<cols && found ; i++)
	{
		string ver = vertical[i];
		if (ver.find(guess) != string :: npos)
		{
			int point= guess.length();
			if (guess.length() > 5)
				point +=2;
			cout << guess << " is found in the column level. It contributes " << point << " points." <<  endl;
			cout << "---";
			found = false;
			score += point;
		}
		else if (ver.find(reversed) != string :: npos)
		{
			int point= guess.length();
			if (guess.length() > 5)
				point +=2;
			cout << guess << " is found in the column level. It contributes " << guess.length() << " points." << endl;
			cout << "---";
			found = false;
			score += point;
		}
	}
}
void findRow(int rows, int & score, string guess, string reversed, bool & found, vector<string> horizontal)
{
	for (int i=0; i<rows && found ; i++)
	{
		string hor = horizontal[i];
		if (hor.find(guess) != string :: npos)
		{
			int point= guess.length();
			if (guess.length() > 5)
				point +=2;
			cout << guess << " is found in the row level. It contributes " << point << " points." <<  endl;
			cout << "---";
			found = false;
			score += point;
		}
		else if (hor.find(reversed) != string :: npos)
		{
			int point= guess.length();
			if (guess.length() > 5)
				point +=2;
			cout << guess << " is found in the row level. It contributes " << point << " points." << endl;
			cout << "---";
			found = false;
			score += point;
		}
	}
}
void findDiagonal(int & score, string guess, string reversed, bool & found, bool &notFound, vector<string> diagonal, vector<string> joker)
{
	for (int i=0; i<diagonal.size() && found ; i++)
	{
		for (int j=0; j<joker.size() && found; j++)
		{
			string cross = diagonal[i];
			string s = joker[j];
			if (cross.find(guess) != string :: npos)
			{
				int point = guess.length()*2;
				if (guess.length() > 5)
					point +=2;
				cout << guess << " is found in the diagonal level. It contributes " << point << " points." <<  endl;
				cout << "---";
				found = false;
				score += point;
			}
			else if (cross.find(reversed) != string :: npos)
			{
				int point = guess.length()*2;
				if (guess.length() > 5)
					point +=2;
				cout << guess << " is found in the diagonal level. It contributes " << point << " points." << endl;
				cout << "---";
				found = false;
				score += point;
			}
			else if (cross.find(s) != string :: npos && found)
			{
				int point = guess.length()*2;
				if (guess.length() > 5)
					point +=2;
				point -=2;
				cout << guess << " is found in the diagonal level. One letter was replaced by joker. It contributes " << point << " points." << endl;
				cout << "---";
				found = false;
				score += point;
			}
			else
				notFound = false;
		}
	}

}

int main()
{
	string fileName;

	vector<vector<char> > mat;

	cout << "This program allows you to play a Sunday morning puzzle on your computer.\n---" << endl;
	cout<<"Enter the matrix file name: ";
	cin>>fileName;
	ifstream input;
	input.open(fileName.c_str());

	while (input.fail())//keeps asking until user enters the proper matrix file name
	{
		cin.clear();
		cout<< "Invalid file name!\n---" << endl;
		cout<<"Enter the matrix file name: ";
		cin>>fileName;	
		input.open(fileName.c_str());
	}

	string line;
	vector <int> inequality;
	while(!input.eof())//until end of the file characters in file will be contained in vector "mat"
	{
		getline(input, line);
		stringstream ss(line);
		char ch;
		vector<char> temp;

		int count=0;// for row equality
		while(ss >> ch)
		{
			temp.push_back(ch);	
			count++;
		}
		mat.push_back(temp);
		inequality.push_back(count);
	}

	for(int e=0; e<inequality.size()-2; e++)// if rows are not equal, program is terminating itself
	{
		if (inequality[e] != inequality [e+1])
		{
			cout << "The matrix does not have row equality, terminating...\n";
			return 0;
		}
	}

	int rows = mat.size()-1; //there is minus one because files that are provided by course  contains a empty line after characters are finished
	int cols = mat[0].size();//column size
	int dif;// it is necessary to determine boundaries either in rows>cols or cols>rows situations
	if (cols > rows)
		dif = cols - rows;
	else 
		dif = rows-cols;

	string guess, reversed;
	cout << "---\nEnter a word: ";
	int score =0;// to calculate score of user

	while (cin >> guess && guess.length() >= 3)// it keeps asking until user enters a word of length less than 3
	{	
		string g,m;
		reversed = guess;
		reversing (reversed);// make a reversed version of input word to make search easier

		vector<string> vertical;
		verticalSearch(rows, cols, mat,vertical);//makes vector suitable for vertical search
		vector<string> horizontal;
		horizontalSearch(rows, cols, mat,horizontal);
		vector <string> diagonal;
		diagonalSearch(rows, cols,dif, mat,diagonal);
		vector <string> joker; //this vector will store all possibilities that input words with one character difference
		jokerSearch(g, m, guess, reversed, joker);

		bool notFound = true;
		bool found = true; //if it becomes false program stops searching further

		findColumn(cols, score, guess, reversed, found, vertical);//tries to find the word in vertical direction
		findRow(rows, score, guess, reversed, found, horizontal);
		findDiagonal(score, guess, reversed, found, notFound, diagonal, joker);//find the word diagonal direction and also if there is joker checks for it

		if (notFound == false && found == true)
		{
			cout << guess << " is not found in the matrix. 5 points are deducted."<<endl;
			cout << "---";
			score -= 5;
		}
		cout << "\nEnter a word: ";
	}
	cout << "---\nGame has ended."<< endl;
	cout << "Total score of the words: " << score << endl;

	return 0;
}
