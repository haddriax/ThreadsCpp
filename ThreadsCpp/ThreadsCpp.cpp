#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <string>
#include <sstream>

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

void SpawnThreads()
{
	threads.reserve(10);

	// Create the threads.
	for (size_t i = 0; i < 10; i++)
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

			{
				std::unique_lock<std::mutex> lck(mtx);
				oss << "Thread" << tId << " has been terminated.\n";
			}

		}
	}

	std::cout << oss.str() << std::endl;
}

int main()
{
	SpawnThreads();
}