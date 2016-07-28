#pragma once

#include "../../core/memory/memory_object.h"

#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>

namespace blowbox
{
	class WorkerThread;

	class Task;
	
	class TaskManager
	{
	public:
		TaskManager();
		~TaskManager();

		static TaskManager* Instance();

		static void WorkThread();

		void StartUp();
		void ShutDown();

		void AddTask(Task* task);

		std::mutex& GetTasksMutex() { return tasks_mutex_; };
		std::queue<Task*> GetTasks() { return tasks_; };
		std::vector<std::thread>& GetThreads() { return threads_; };
		std::condition_variable& GetTaskAdded() { return task_added_; };
	public:
		std::mutex tasks_mutex_;
		std::queue<Task*> tasks_;
		std::vector<std::thread> threads_;
		std::condition_variable task_added_;
	};
}