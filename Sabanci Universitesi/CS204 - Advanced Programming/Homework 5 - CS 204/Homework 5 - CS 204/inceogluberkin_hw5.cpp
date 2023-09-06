#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <fstream>
#include "Queue.h"
#include "randgen.h"

using namespace std;

Queue globalQue;
mutex mutexPro, mutexCon, print;
bool EXHAUSTED = false;

bool mutexIsEmpty ()
{
	bool condition = false;
	mutexCon.lock();
	if (globalQue.isEmpty())
	{
		condition = true;
	}

	mutexCon.unlock();

	return condition ;
}

void producer (int id, Queue & mainQueue)
{
	RandGen rand;
	int randomNum = rand.RandInt(1000,4000);
	print.lock();
	cout << "Producer Thread " << id << " - starts sleeping for " << randomNum << " milliseconds.\n";
	print.unlock();
	this_thread::sleep_for (chrono::milliseconds(randomNum));

	while (!mainQueue.isEmpty())
	{
		string fileName;
		mutexPro.lock();
		mainQueue.dequeue(fileName);
		cout << "Producer Thread " << id << " - is now enqueuing \"" << fileName <<"\"\n";
		globalQue.enqueue(fileName);
		mutexPro.unlock();
		randomNum = rand.RandInt(1000,4000);
		print.lock();
		cout << "Producer Thread " << id << " - starts sleeping for " << randomNum << " milliseconds.\n";
		print.unlock();
		this_thread::sleep_for (chrono::milliseconds(randomNum));

	}

	if(mainQueue.isEmpty()) 
	{
		cout << "Producer Thread " << id << " - cannot find any file to enqueue, joining... \n";
		EXHAUSTED = true;
	}

}

void consumer (int id)
{
	ifstream input;
	RandGen rand;

	int randomNum = rand.RandInt(2500,3500);
	print.lock();
	cout << "Consumer Thread " << id << " - starts sleeping for " << randomNum << " milliseconds.\n";
	print.unlock();
	this_thread::sleep_for (chrono::milliseconds(randomNum));

	string fileName;

	while(!mutexIsEmpty())
	{
		//mutexCon.lock();
		globalQue.dequeue(fileName);
		print.lock();
		cout << "Consumer Thread " << id << " - is now handling \"" << fileName << "\" \n";
		print.unlock();
	
		input.open(fileName);

		if (!input)
		{
			print.lock();
			cout << "Consumer Thread " << id << " - cannot process \"" << fileName << "\", there is no such file!\n";
			print.unlock();
		}
		if (globalQue.isEmpty() && !EXHAUSTED) 
		{
			print.lock();
			cout << "Consumer Thread " << id << " - cannot find any file to dequeue for now.\n";
			print.unlock();
		}

		//mutexCon.unlock();

		input.close();

		
	}//End of loop

	if (EXHAUSTED) 
	{
		print.lock();
		cout << "Consumer Thread " << id << " - cannot find any file to dequeue, joining...\n";
		print.unlock();
		return;
	}

	randomNum = rand.RandInt(2500,3500);
	print.lock();
	cout << "Consumer Thread " << id << " - starts sleeping for " << randomNum << " milliseconds.\n";
	print.unlock();
	this_thread::sleep_for (chrono::milliseconds(randomNum));
}

void decyrption (string fileName);
void reversingQueue (Queue & q);

int main()
{
	Queue mainQ;
	string fileName;
	cout << "Please enter a file name: ";
	cin >> fileName;

	while (fileName != "-")
	{
		mainQ.enqueue(fileName);
		cout << "Please enter a file name: ";
		cin >> fileName;
	}
	reversingQueue(mainQ);

	thread producer1 (&producer, 1, ref(mainQ));
	thread producer2 (&producer, 2, ref(mainQ));
	thread consumer1 (&consumer, 1);
	thread consumer2 (&consumer, 2);
	thread consumer3 (&consumer, 3);

	producer1.join();
	producer2.join();

	consumer1.join();
	consumer2.join();
	consumer3.join();

	cin.get();
	cin.ignore();
	cout << "All threads have joined with main, exiting...\n";
	return 0; 
}

void decyrption (string fileName)
{

	int max=0;
	char mostCommon = ' ';
	string line;
	ifstream input;
	input.open(fileName);

	stringstream ss;
	string whole;
	while (getline(input, line))
	{
		stringstream ss (line);
		whole += line;
	}
	char ch;
	stringstream full (whole);
	stringstream counter (whole);
	while ( full >> ch)
	{
		int count =0;
		char next;
		while (counter>>next)
		{
			if (next == ch)
				count++;
		}
		if (count > max)
		{
			max = count;
			mostCommon = ch;
		}
		counter.clear();
		counter.seekg(0);
	}

	char difference = 'e' - mostCommon + 26;
	if (difference == 26)
		difference = 0;
	else if (difference > 26)
		difference -= 26; 

	full.clear();
	full.seekg(0);
	string outputFile = fileName + "_decrypted.txt";
	ofstream out;
	out.open(outputFile);
	input.clear();
	input.seekg(0);
	char change;
	while (input.get(change))
	{
		if (change + difference > 122)
		{
			change += difference -26;
			out << change;
		}
		else if ( change == ' ')
			out << ' ';
		else if ( change < 97)
			out << change;
		else
		{
			change += difference ;
			out << change;
		}

	}

	out.close();

}

void reversingQueue (Queue & q)
{
	vector <string> storage;
	string s;
	while (!q.isEmpty())
	{
		q.dequeue(s);
		storage.push_back(s);
	}
	string t;
	int size = storage.size();
	for (int i=0; i<size ; i++)
	{
		t = storage.back();
		storage.pop_back();
		q.enqueue(t);
	}
}
