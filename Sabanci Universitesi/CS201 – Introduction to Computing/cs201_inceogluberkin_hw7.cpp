#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
//Berkin Inceoglu 23641 CS201- HW7 2018 Spring
using namespace std;

struct team // struct that has every feature of any club
{
	string teamname;
	int points;
	int played;
	int wins;
	int losses;
	int scored;
	int conceded;
	int goalDifference;
	
};
int main()
{
	ifstream input;
	string fileName, teamName;

	cout << "Please enter a filename: ";
	cin>> fileName;
	input.open(fileName.c_str());

	while (input.fail()) // if input cant manage to open a file that has been entered it gives an error and ask againt until user enters a right input
	{	
		cout << "Program cannot open " << fileName << endl;
		cout << "Please enter a filename: ";
		cin >> fileName;
		input.open(fileName.c_str());
	}

	cout << "Please enter a team name: ";
	cin>> teamName;

	string t1, t2;//to get home and away team names
	int sc1, sc2;//to get home and away goals
	string line; // line that contains result
	vector <team> table; // to store features of every club in the league 

	while (getline(input, line))
	{
		istringstream results(line); // transforming string into inputstring stream to get 4 stuff in that line which are home team home score and away team away score
		results >> t1>> sc1 >> sc2 >> t2;
		bool t1exists = false; //boolean functions for that any team played a home game
		bool t2exists = false;//boolean functions for that any team played a away game

		for (int i=0; i<table.size();i++) //by this loop computer gets every stat of every club in the league, creates a one size for every club 
		{
			if(table[i].teamname == t1) //checks if a team plays at home and condition adds how many times they played, how many wins, defeats and draws they get and also how many goals they scored, conceed and their difference
			{// if team exists
				t1exists = true;

				table[i].played++;
				table[i].scored += sc1;
				table[i].conceded += sc2;
				table[i].goalDifference += sc1 - sc2;

				if(sc1>sc2)
				{
					table[i].wins ++;
					table[i].points += 3;
				}
				else if(sc1<sc2)
					table[i].losses ++;
				else
					table[i].points ++;
			}

			if(table[i].teamname == t2) // same as first, if it performs for a teams away games which means when they are string t2
			{
				t2exists = true;

				table[i].played++;
				table[i].scored += sc2;
				table[i].conceded += sc1;
				table[i].goalDifference += sc2 - sc1;

				if(sc2>sc1)
				{
					table[i].wins ++;
					table[i].points += 3;
				}
				else if(sc2<sc1)
					table[i].losses ++;
				else
					table[i].points++;
			}
		}

		if(!t1exists) // if there is a new team that is not examined before ,this condition makes a new struct for it to be calculated 
		{
			team i;
			i.teamname = t1;
			i.scored = sc1;
			i.conceded =sc2;
			i.goalDifference = sc1-sc2;
			i.played = 1;
			i.wins = 0;
			i.losses = 0; //start without wins, defeats and points
			i.points = 0;

			if(sc1>sc2)
			{
				i.wins = 1;
				i.points = 3; //if they win their points would be 3 
			}
			else if(sc1<sc2)//does not add points due to rules of football
				i.losses = 1;
			else
				i.points = 1;

			table.push_back(i);
		}

		if(!t2exists)//same as t1exists
		{
			team i2;
			i2.teamname = t2;
			i2.scored = sc2;
			i2.conceded =sc1;
			i2.goalDifference = sc2-sc1;
			i2.played = 1;
			i2.wins = 0;
			i2.points = 0;
			i2.losses = 0;
			if(sc2>sc1)
			{
				i2.wins = 1;
				i2.points = 3;
			}
			else if(sc2<sc1)
				i2.losses = 1;
			else
				i2.points = 1;

			table.push_back(i2);
		}
	}

	for(int i=0; i<table.size()-1; i++)//first team to be compared
	{
		for(int j = i+1; j<table.size(); j++)//and second which is compared by i
		{
			if (table[i].points < table[j].points || (table[i].points == table[j].points  && table[i].goalDifference < table[j].goalDifference) || (table[i].points == table[j].points  && table[i].goalDifference == table[j].goalDifference && table[i].teamname > table[j].teamname)){
				team temp = table[i];
				table[i] = table[j];
				table[j] = temp;
			}
		}
	}
	bool teamExists = false; //necessary for wrong team input
	for (int i = 0; i< table.size(); i++)
	{
		if(teamName == table[i].teamname) //prints the all features required in homework
		{
			teamExists = true;
			cout << "Rank: " << i+1 << endl;
			cout << "Matches played: " << table[i].played << endl;
			cout << "Wins: " << table[i].wins << endl;
			cout << "Draws: " << table[i].played - (table[i].wins + table[i].losses) << endl;
			cout << "Losts: " << table[i].losses << endl;
			cout << "Goals scored: " << table[i].scored << endl;
			cout << "Goals conceded: " << table[i].conceded << endl;
			cout << "Goal difference: " << table[i].goalDifference << endl;
			cout << "Points: " << table[i].points<< endl;
		}
	}

	if (!teamExists) // in case of writing a team name that does not exist
	{
		cout << "There is no such team!"<< endl;
	}

	return 0;
}
