/*
This program is intended to achieve Asynchronous operation of LCR algorithm.
Here, all the threads operate asynchronously meaning, different processes operate in different rounds.
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

mutex mtx;
int num_threads;
vector<queue<long>> QueueArray; //This creates a vector of type queue


void Asynch_LCR(long threadid, int thread_no){
	int rounds = num_threads;
	long max = threadid;
	bool push_max = true;
	
	int op_t_id = (thread_no+1) % num_threads;
	
	while(rounds>0){
		int delay = rand()%12+1; //generates a random number from the range 1-12
		sleep_for(nanoseconds(delay)); //The random number is used for delay in pushing the value to the output queue
		if (push_max)
		{
			QueueArray[op_t_id].push(max); //If a new max is found, thread outputs the new maximum, else 0
		}
		else
		{
			QueueArray[op_t_id].push(0);
		}
		push_max = false;
		
		while(QueueArray[thread_no].size() == 0);
		{
			sleep_for(milliseconds(10));
		}
		//retrieving the elements from the input queue, since it is asynch operation, queue might contain more than one element, Hence the for loop
		for (int h=0; h < QueueArray[thread_no].size();h++) 
		 {
		 	long incoming = QueueArray[thread_no].front();
		 	
		 	if(incoming>threadid)
			{
				max = incoming; //New maximum found from the input queue
				push_max = true;
			}
			QueueArray[thread_no].pop();
		 }
		rounds--; //Each thread runs n rounds asynchronously. 
	}
	mtx.lock();
	cout <<"My ID is "<<threadid<<" and my leader is "<<max << endl ; //After the completion of n rounds, the leader is displayed by each process
	mtx.unlock();
}

int main(){
	int i=0;
    long data;
	
	ifstream infile;
	infile.open("input.dat");            // This file contains the input data
	infile >> data;                      //This initial data contains the value of number of threads
	num_threads = (int)data;
	
	long pid_list[num_threads] = {};      //pid_list is the variable that contains the process_ids
	
	//create a number vector of size n and add the numbers to it in while loop
	while( !infile.eof() ){
		infile >> data;
		pid_list[i++] = data;
	}
	infile.close();
	
	for(int h=0; h <num_threads; h++)
	{
		QueueArray.push_back(queue<long>()); //we add n empty queues to the vector
	}

	thread threads[num_threads]; //Creation of n threads
	
	for(int k=0; k <num_threads; k++)
	{ 	
		threads[k] = thread(Asynch_LCR, pid_list[k], k);	
	}

	for( i = 0; i < num_threads; i++ ) 
	{
		threads[i].join();
	}
	
	return(0);
}
