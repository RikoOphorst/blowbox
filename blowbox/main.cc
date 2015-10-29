#include "../blowbox/core/blowbox.h"
#include "../blowbox/window/window.h"
#include "../blowbox/graphics/direct3d/renderer.h"
#include "../blowbox/core/threading/job_manager.h"
#include "../blowbox/core/threading/job.h"

#include <iostream>
#include <chrono>

using namespace blowbox;
using namespace blowbox::direct3d;

class DataStorage
{
public:
	DataStorage() : iterations(0), ended(false) {}
	bool ended;
	int iterations;
};

bool test_if_prime(int i)
{
	for (int j = 2; j <= i / 2; j++)
		if (!(i % j))
			return false;

	return true;
}

void evaluate_primes(int thread_id, int job, int begin, int end)
{
	int sum = 0;
	
	for (int i = begin; i < end; i++)
	{
		if (test_if_prime(i))
		{
			printf("Thread %d | Job %d: %d\n", thread_id, job, i);
		}
	}
}

void Job1(int thread_id, void* mem_ptr, int mem_size)
{
	evaluate_primes(thread_id, 1, 0, 100000);
}

void Job2(int thread_id, void* mem_ptr, int mem_size)
{
	evaluate_primes(thread_id, 2, 0, 100000);
}

void Job3(int thread_id, void* mem_ptr, int mem_size)
{
	evaluate_primes(thread_id, 3, 0, 100000);
}

void Job4(int thread_id, void* mem_ptr, int mem_size)
{
	evaluate_primes(thread_id, 4, 0, 100000);
}

void Job5(int thread_id, void* mem_ptr, int mem_size)
{
	evaluate_primes(thread_id, 5, 0, 100000);
}

void Job6(int thread_id, void* mem_ptr, int mem_size)
{
	evaluate_primes(thread_id, 6, 0, 100000);
}

void Job7(int thread_id, void* mem_ptr, int mem_size)
{
	evaluate_primes(thread_id, 7, 0, 100000);

	static_cast<DataStorage*>(mem_ptr)->ended = true;
}

int main(int argc, char** argv)
{
	JobManager::Instance()->StartUp();

	DataStorage* ds = new DataStorage();

	std::vector<Job*> jobs;
	jobs.push_back(new Job(Job1, nullptr, 0));
	jobs.push_back(new Job(Job2, nullptr, 0));
	jobs.push_back(new Job(Job3, nullptr, 0));
	jobs.push_back(new Job(Job4, nullptr, 0));
	jobs.push_back(new Job(Job5, nullptr, 0));
	jobs.push_back(new Job(Job6, nullptr, 0));
	jobs.push_back(new Job(Job7, ds, sizeof(ds)));

	// Job::others is a vector of Job* that need to be finished before the job gets executed.
	// The following lines adds all other jobs that need to be added to last job (job 7) 

	jobs[6]->others.push_back(jobs[0]); // Job 7 has to wait on job 1
	jobs[6]->others.push_back(jobs[1]); // Job 7 has to wait on job 2
	jobs[6]->others.push_back(jobs[2]); // Job 7 has to wait on job 3
	jobs[6]->others.push_back(jobs[3]); // Job 7 has to wait on job 4
	jobs[6]->others.push_back(jobs[4]); // Job 7 has to wait on job 5
	jobs[6]->others.push_back(jobs[5]); // Job 7 has to wait on job 6

	// Add all the jobs to the JobManager
	for (int i = 0; i < jobs.size(); i++)
	{
		JobManager::Instance()->AddJobToQueue(jobs[i]);
	}

	while (ds->ended == false)
	{
		ds->iterations++;
	}

	printf("All jobs have finished!\n");

	std::cin.get();

	return 0;
}