#pragma once

#include "../../core/memory/memory_object.h"

#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <vector>

using namespace blowbox::memory;

namespace blowbox
{
	class Task;
	
	/**
	* @class blowbox::TaskManager
	* @author Riko Ophorst
	* @brief The TaskManager is responsible for handling all things multithreading in the application
	*/
	class TaskManager : public MObject
	{
	public:
		/**
		* @brief Factory to create the TaskManager instance
		* @param[in]	allocator	The allocator that should be used to allocate the TaskManager
		*/
		static TaskManager* Create(Allocator* allocator);

		/**
		* @brief Singleton accessor to the instance of the TaskManager
		*/
		static TaskManager* Instance();

		/**
		* @brief TaskManager constructor
		*/
		TaskManager(Allocator* allocator);

		/**
		* @brief TaskManager destructor
		*/
		~TaskManager();

		/**
		* @brief A low-level thread, manages task selection from all available tasks and executes accordingly
		*/
		static void WorkThread();

		/**
		* @brief Starts up the task manager
		*/
		void StartUp();

		/**
		* @brief Shuts down the task manager
		*/
		void ShutDown();

		/**
		* @brief Adds a task to the task manager and will be executed as soon as possible
		* @param[in]	task	The task you want to add
		*/
		void AddTask(Task* task);

		std::mutex& GetTasksMutex(); //!< Get the mutex for accessing the tasks object
		const std::vector<Task*>& GetTasks(); //!< Get all tasks currently in the execution queue (so no tasks that are already executing or have finished executing)
		std::vector<std::thread>& GetThreads(); //!< Get all the hardware threads the task manager uses
		std::condition_variable& GetCheckForTask(); //!< Get the condition variable used for (un)blocking the worker threads
	public:
		static TaskManager* instance_; //!< Singleton instance of TaskManager

		bool running_; //!< Is the task manager running?

		std::mutex tasks_mutex_; //!< Mutex used for modifying the tasks queue
		std::vector<Task*> tasks_; //!< All the tasks that are queued up for execution
		std::vector<std::thread> threads_; //!< All threads working to execute the tasks
		std::condition_variable check_for_task_; //!< CV used for (un)blocking the worker threads
	};
}