//#pragma once
//
//#include <condition_variable>
//#include <mutex>
//#include <thread>
//#include <queue>
//
//#include "../../core/threading/job.h"
//
////#undef AddJob
//
//namespace blowbox
//{
//	class WorkerThread;
//	
//	class JobManager
//	{
//	public:
//		JobManager();
//		~JobManager();
//
//		static JobManager* Instance();
//
//		void StartUp();
//		void ShutDown();
//
//		void AddJobToQueue(Job* job);
//		std::queue<Job*>& GetJobQueue();
//		std::condition_variable& GetJobAddedCV();
//		std::mutex& GetJobMutex();
//
//	private:
//		std::mutex job_mutex_;
//		std::queue<Job*> jobs_;
//		std::vector<WorkerThread*> workers_;
//		std::condition_variable job_added_;
//	};
//}