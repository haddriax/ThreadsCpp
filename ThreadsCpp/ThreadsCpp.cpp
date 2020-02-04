#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <string>
#include <sstream>

#include "CustomFunctor.h"

std::vector<std::thread> threads;
std::mutex mtx;
std::ostringstream oss;

void ThreadAction(int _id)
{
	for (size_t i = 0; i < 50; i++)
	{
		// Simulate work with no datas access.
		std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(10));

		//Locking data access for this scope.
		{
			std::unique_lock<std::mutex> lck(mtx);
			oss << "Thread " << std::to_string(_id) << ", iteration : " << std::to_string(i) << "\n";
		}
	}
}

void SpawnThreads(int _threadsNumber)
{
	threads.reserve(_threadsNumber);

	// Create the threads.
	for (size_t i = 0; i < _threadsNumber; i++)
	{
		threads.push_back(std::thread(ThreadAction, i));
	}

	// Join every thread.
	for (auto& const t : threads)
	{
		if (t.joinable())
		{
			std::thread::id tId = t.get_id();
			t.join();

			// Print threads info after join() called.
			{
				std::unique_lock<std::mutex> lck(mtx);
				oss << "Thread" << tId << " terminated.\n";
			}

		}
	}

	// LAMBDA THREAD
	// Print full message in thread.
	std::thread lambdaThread([]()
	{
		std::cout << oss.str() << std::endl;
	});

	if (lambdaThread.joinable())
		lambdaThread.join();

	// FUNCTOR THREAD
	CustomFunctor customFunctor;
	std::thread functorThread(customFunctor);
	
	if (functorThread.joinable())
		functorThread.join();

	// FUNCTOR ARRAY PARAMETERS THREAD
	const int arraySize = 5;
	int arr[arraySize] = { 0, 1, 2, 3, 4 };
	CustomFunctorParam customFunctorParam;
	std::thread functorThreadParam(customFunctorParam, arr, arraySize);

	if (functorThreadParam.joinable())
		functorThreadParam.join();
}

int main()
{
	SpawnThreads(10);
}