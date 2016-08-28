#include "task_manager.h"

#include "../../core/threading/task.h"
#include "../../core/console/console.h"

namespace blowbox
{
	TaskManager* TaskManager::instance_ = nullptr;

	//------------------------------------------------------------------------------------------------------
	TaskManager::TaskManager(Allocator* allocator) :
		MObject(allocator),
		running_(false)
	{
		StartUp();
	}

	//------------------------------------------------------------------------------------------------------
	TaskManager::~TaskManager()
	{
		ShutDown();
	}
	
	//------------------------------------------------------------------------------------------------------
	TaskManager* TaskManager::Create(Allocator* allocator)
	{
		return instance_ = MemoryManager::Allocate<TaskManager>(allocator, allocator);
	}

	//------------------------------------------------------------------------------------------------------
	TaskManager* TaskManager::Instance()
	{
		return instance_;
	}

	//------------------------------------------------------------------------------------------------------
	void TaskManager::WorkThread()
	{
		TaskManager* instance = Instance();

		while (instance == nullptr)
		{
			instance = Instance();
		}

		while (true)
		{
			std::unique_lock<std::mutex> lck(instance->tasks_mutex_);
			Instance()->check_for_task_.wait(lck);

			if (!instance->running_)
				break;
			
			Task* task = nullptr;
			{
				if (instance->tasks_.size() == 0)
				{
					lck.unlock();
					continue;
				}

				for (int i = 0; i < instance->tasks_.size(); i++)
				{
					if (!instance->tasks_[i]->HasToWaitForDependencies())
					{
						task = Instance()->tasks_[i];
						instance->tasks_.erase(instance->tasks_.begin() + i);
						break;
					}
				}

				if (task == nullptr)
				{
					task = instance->tasks_.front();
					instance->tasks_.erase(instance->tasks_.begin());
				}
			}

			lck.unlock();

			task->Execute();

			instance->check_for_task_.notify_one();
		}
	}

	//------------------------------------------------------------------------------------------------------
	void TaskManager::StartUp()
	{
		int hwc = std::thread::hardware_concurrency();
		for (int i = 0; i < hwc; i++)
		{
			threads_.push_back(std::thread(WorkThread));
		}

		running_ = true;
	}

	//------------------------------------------------------------------------------------------------------
	void TaskManager::ShutDown()
	{
		running_ = false;

		check_for_task_.notify_all();

		for (int i = 0; i < threads_.size(); i++)
		{
			threads_[i].join();
		}
	}

	//------------------------------------------------------------------------------------------------------
	void TaskManager::AddTask(Task* job)
	{
		{
			std::lock_guard<std::mutex> guard(tasks_mutex_);
			tasks_.push_back(job);
		}

		check_for_task_.notify_one();
	}
	
	//------------------------------------------------------------------------------------------------------
	std::mutex& TaskManager::GetTasksMutex()
	{
		return tasks_mutex_;
	}

	//------------------------------------------------------------------------------------------------------
	const std::vector<Task*>& TaskManager::GetTasks()
	{
		return tasks_;
	}

	//------------------------------------------------------------------------------------------------------
	std::vector<std::thread>& TaskManager::GetThreads()
	{
		return threads_;
	}

	//------------------------------------------------------------------------------------------------------
	std::condition_variable& TaskManager::GetCheckForTask()
	{
		return check_for_task_;
	}
}