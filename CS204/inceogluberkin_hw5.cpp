#include <iostream>
#include "Queue.h"
#include "randgen.h"
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <fstream>

using namespace std;

Queue mq;
mutex myMutex, enq, m, t, print;

void producer (int i, Queue & q)
{

	RandGen random;
	int a = random.RandInt(1000,4000);
	print.lock();
	cout << "Producer Thread " << i << " - starts sleeping for " << a << " milliseconds.\n";
	print.unlock();
	this_thread::sleep_for (chrono::milliseconds(a));

	if (!q.isEmpty())
	{
		string s;
		enq.lock();
		q.dequeue(s);
		cout << "Producer Thread " << i << " - is now enqueueing \"" << s <<"\"\n";
		mq.enqueue(s);
		enq.unlock();
		a = random.RandInt(1000,4000);
		print.lock();
		cout << "Producer Thread " << i << " - starts sleeping for " << a << " milliseconds.\n";
		print.unlock();
		this_thread::sleep_for (chrono::milliseconds(a));
	}
	else 
	{
		cout << "Producer Thread " << i << " - cannot find any file to enqueue, joining... \n";
	}

}

void consumer (int i)
{
	ifstream inputFile;
	RandGen random;
	int a = random.RandInt(2500,3500);
	print.lock();
	cout << "Consumer Thread " << i << " - starts sleeping for " << a << " milliseconds.\n";
	print.unlock();
	this_thread::sleep_for (chrono::milliseconds(a));

	
	string s;
	if(!mq.isEmpty())
	{
		enq.lock();
		mq.dequeue(s);
		print.lock();
		cout << "Consumer Thread " << i << " - is now handling \"" << s << "\" \n";
		print.unlock();
		enq.unlock();
		inputFile.open(s);
		if (!inputFile)
		{
			print.lock();
			cout << "Consumer Thread " << i << " - cannot process \"" << s << "\", there is no such file!\n";
			print.unlock();
		}
	}
	else 
	{
		print.lock();
		cout << "Consumer Thread " << i << " - cannot find any file to dequeue for now.\n";
		print.unlock();
	}

	a = random.RandInt(2500,3500);
	print.lock();
	cout << "Consumer Thread " << i << " - starts sleeping for " << a << " milliseconds.\n";
	print.unlock();
	this_thread::sleep_for (chrono::milliseconds(a));
	
}

int main()
{
	Queue myQueue;
	string filename;
	cout << "Please enter a file name: ";
	cin >> filename;
	while (filename != "-")
	{
		myQueue.enqueue(filename);
		cout << "Please enter a file name: ";
		cin >> filename;
	}

	thread producer1 (&producer,1, ref(myQueue));
	thread producer2 (&producer,2, ref(myQueue));
	thread consumer1 (&consumer, 1);
	thread consumer2 (&consumer, 2);
	thread consumer3 (&consumer, 3);

	producer1.join();
	producer2.join();
	consumer1.join();
	consumer2.join();
	consumer3.join();

	return 0; 
}