#include "blowbox/blowbox_include.h"
#include "blowbox/core/threading/task.h"

#include <iostream>
#include <string>
#include <vector>
#include <comdef.h>
#include <chrono>

#define BB_CONSOLE_SERVER_PORT 60000
#define BB_CONSOLE_MAX_CLIENTS 1

#include "sum-numbers.h"

using namespace blowbox;
using namespace blowbox::direct3d;
using namespace blowbox::memory;

typedef std::chrono::high_resolution_clock Clock;

int main(int argc, char** argv)
{
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	
	// Create & initialize blowbox.
	Blowbox* blowbox = Blowbox::Create();
	blowbox->Initialise();

	// Allocator we use to allocate our memory with
	FreeListAllocator* allocator = MemoryManager::FreeListAllocator(50000);

	// Create & initialize the task manager
	TaskManager::Create(allocator);
	TaskManager::Instance()->StartUp();

	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

	float tasks = 1;						//!< The amount of tasks the work load should be split into
	float data_size = 100000;				//!< The amount of dummy data to create
	float task_size = data_size / tasks;	//!< The chunk of data one task has to process
	std::vector<Task*> all_tasks;			//!< Vector to store all tasks
	std::vector<TaskContext*> all_contexts;	//!< Vector to store all task contexts
	std::mutex finished_mutex;				//!< Mutex to provide thread-safety to the finished flag
	bool finished = false;					//!< Defines whether the sum-routine is completed
	
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

	// Create the data we will be feeding to our tasks (aka threads) to actually let them process some data
	std::vector<unsigned long long> numbers;
	for (int i = 0; i < data_size; i++)
	{
		numbers.push_back(i);
	}

	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

	// Build all the sum-tasks that we will use to process our data
	for (int i = 0; i < (int)tasks; i++)
	{
		// The context we will be using for this task, we pass it the correct set of numbers taken from our original dummy data
		SumNumbersTask::Context* context = MemoryManager::Allocate<SumNumbersTask::Context>(allocator);
		context->numbers = std::vector<unsigned long long>(numbers.begin() + (i * task_size), numbers.begin() + ((i + 1) * task_size));
		context->result = 0;
		
		// The actual task itself, given a certain context
		SumNumbersTask* task = MemoryManager::Allocate<SumNumbersTask>(allocator, context);

		// Add the task to the manager & cache the pointers to the task and context
		TaskManager::Instance()->AddTask(task);
		all_tasks.push_back(task);
		all_contexts.push_back(context);
	}

	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

	// Build the exit task, so that we can identify when the sum-routine is finished
	SumNumbersExitTask::Context* exit_context = MemoryManager::Allocate<SumNumbersExitTask::Context>(allocator);
	exit_context->finished_mutex = &finished_mutex;
	exit_context->finished = &finished;

	// The actual exit task itself
	SumNumbersExitTask* exit_task = MemoryManager::Allocate<SumNumbersExitTask>(allocator, exit_context);

	// Make the exit task depend on all the sum-tasks
	for (int i = 0; i < all_tasks.size(); i++)
	{
		exit_task->AddDependency(all_tasks[i]);
	}

	// Add the task to the task manager
	TaskManager::Instance()->AddTask(exit_task);

	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

	auto t1 = Clock::now();

	// Now we wait for the sum-routine to be completely finished
	while (true) 
	{
		std::lock_guard<std::mutex> lck(finished_mutex);
		if (finished)
		{
			break;
		}
	}

	auto t2 = Clock::now();

	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

	// Now that we know we're finished executing the sum-routine, we can accumulate the results of all subtasks
	unsigned long long total_result = 0;

	// Actually accumulate the results of all contexts
	for (int i = 0; i < all_tasks.size(); i++)
	{
		total_result += reinterpret_cast<SumNumbersTask::Context*>(all_tasks[i]->context_)->result;
	}

	// Log the final result of the sum-routine
	Console::Instance()->Log("Finished summing, total: " + std::to_string(total_result), BB_MESSAGE_TYPE_LOG);
	Console::Instance()->Log(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()) + " milliseconds", BB_MESSAGE_TYPE_LOG);

	// Wait for user input
	std::cin.get();

	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

	// Now it's time to shut the application down
	TaskManager::Instance()->ShutDown();

	// Deallocate everything
	MemoryManager::Deallocate(allocator, TaskManager::Instance());
	MemoryManager::Deallocate(allocator, exit_task);
	MemoryManager::Deallocate(allocator, exit_context);

	for (int i = 0; i < all_tasks.size(); i++)
	{
		MemoryManager::Deallocate(allocator, all_tasks[i]);
		MemoryManager::Deallocate(allocator, all_contexts[i]);
	}

	// Now deallocate the allocator
	MemoryManager::DestructAllocator(allocator);

	// Shutdown blowbox
	blowbox->Shutdown();

	return 0;
}