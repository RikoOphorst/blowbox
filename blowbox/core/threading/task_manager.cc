//#include "task_manager.h"
//
//#include "../../core/threading/worker_thread.h"
//#include "../../core/threading/task.h"
//#include "../../core/console/console.h"
//
//namespace blowbox
//{
//	//------------------------------------------------------------------------------------------------------
//	TaskManager::TaskManager()
//	{
//
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	TaskManager::~TaskManager()
//	{
//
//	}
//	
//	//------------------------------------------------------------------------------------------------------
//	TaskManager* TaskManager::Instance()
//	{
//		static TaskManager* ptr = new TaskManager();
//		return ptr;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void TaskManager::WorkThread()
//	{
//		while (true)
//		{
//			std::unique_lock<std::mutex> lck(Instance()->tasks_mutex_);
//			Instance()->task_added_.wait(lck);
//			
//			Task* task;
//			{
//				task = Instance()->tasks_.front();
//				Instance()->tasks_.pop();
//			}
//
//			lck.unlock();
//
//			Console::Instance()->Log(std::string("Start executing task: ") + std::to_string((uintptr_t)task), BB_MESSAGE_TYPE_WARNING);
//			task->Execute();
//			Console::Instance()->Log(std::string("Finished executing task: ") + std::to_string((uintptr_t)task), BB_MESSAGE_TYPE_WARNING);
//		}
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void TaskManager::StartUp()
//	{
//		int hwc = std::thread::hardware_concurrency();
//		for (int i = 0; i < hwc; i++)
//		{
//			threads_.push_back(std::thread(WorkThread));
//		}
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void TaskManager::ShutDown()
//	{
//		
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void TaskManager::AddTask(Task* job)
//	{
//		{
//			std::lock_guard<std::mutex> guard(tasks_mutex_);
//			tasks_.push(job);
//		}
//		task_added_.notify_one();
//	}
//}