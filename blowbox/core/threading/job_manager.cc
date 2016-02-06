//#include "job_manager.h"
//
//#include "../../core/threading/worker_thread.h"
//#include "../../core/threading/job.h"
//
//namespace blowbox
//{
//	//------------------------------------------------------------------------------------------------------
//	JobManager::JobManager()
//	{
//
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	JobManager::~JobManager()
//	{
//
//	}
//	
//	//------------------------------------------------------------------------------------------------------
//	JobManager* JobManager::Instance()
//	{
//		static JobManager* ptr = new JobManager();
//		return ptr;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void JobManager::StartUp()
//	{
//		int hwc = std::thread::hardware_concurrency();
//		for (int i = 0; i < hwc; i++)
//		{
//			workers_.push_back(WorkerThread::MakeWorkerThread(i));
//		}
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void JobManager::ShutDown()
//	{
//
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void JobManager::AddJobToQueue(Job* job)
//	{
//		std::lock_guard<std::mutex> guard(job_mutex_);
//
//		jobs_.push(job);
//		job_added_.notify_one();
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	std::queue<Job*>& JobManager::GetJobQueue()
//	{
//		return jobs_;
//	}
//	
//	//------------------------------------------------------------------------------------------------------
//	std::condition_variable& JobManager::GetJobAddedCV()
//	{
//		return job_added_;
//	}
//	
//	//------------------------------------------------------------------------------------------------------
//	std::mutex& JobManager::GetJobMutex()
//	{
//		return job_mutex_;
//	}
//}