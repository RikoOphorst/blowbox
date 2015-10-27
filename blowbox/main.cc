#include "../blowbox/core/blowbox.h"
#include "../blowbox/window/window.h"
#include "../blowbox/graphics/direct3d/renderer.h"
#include "../blowbox/core/threading/job_manager.h"
#include "../blowbox/core/threading/job.h"

#include <iostream>

using namespace blowbox;
using namespace blowbox::direct3d;

struct Something
{
	Something(int job_id, int begin, int end) : job_id(job_id), begin(begin), end(end) {};
	int begin;
	int end;
	int job_id;
};

bool test_if_prime(int i)
{
	for (int j = 2; j <= i / 2; j++)
		if (!(i % j))
			return false;

	return true;
}

void evaluate_primes(int thread_id, void* mem_ptr, int mem_size)
{
	for (int i = static_cast<Something*>(mem_ptr)->begin; i < static_cast<Something*>(mem_ptr)->end; i++)
	{
		if (test_if_prime(i))
		{
			printf("Thread %d | Job %d: %d\n", thread_id, static_cast<Something*>(mem_ptr)->job_id, i);
		}
	}
}

int main(int argc, char** argv)
{
 	JobManager::Instance()->StartUp();

	for (int i = 0; i < 100; i++)
	{
		Something* sm = new Something(i, i * 10000, (i + 1) * 10000 );

		JobManager::Instance()->AddJobToQueue(Job(evaluate_primes, static_cast<void*>(sm), sizeof(sm)));
	}

	while (true) {}

	return 0;
}