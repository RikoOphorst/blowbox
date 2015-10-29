#include "worker_thread.h"

#include "../../core/threading/job_manager.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	WorkerThread::WorkerThread(int id) :
		thread_(WorkerThread::ThreadFunction, id)
	{
		
	}

	//------------------------------------------------------------------------------------------------------
	WorkerThread::~WorkerThread()
	{

	}

	//------------------------------------------------------------------------------------------------------
	WorkerThread* WorkerThread::MakeWorkerThread(int id)
	{
		return new WorkerThread(id);
	}

	//------------------------------------------------------------------------------------------------------
	void WorkerThread::ThreadFunction(int id)
	{
		start:
		{
			std::queue<Job*>& job_queue = JobManager::Instance()->GetJobQueue();
			std::condition_variable& job_added_cv = JobManager::Instance()->GetJobAddedCV();
			std::mutex& job_mutex = JobManager::Instance()->GetJobMutex();

			std::unique_lock<std::mutex> lock(job_mutex);
			while (job_queue.empty())
				job_added_cv.wait(lock);

			Job* job = job_queue.front();

			bool runnable = true;

			for (int i = 0; i < job->others.size(); i++)
			{
				if (job->others[i]->finished == false)
					runnable = false;
			}

			if (runnable)
			{
				job_queue.pop();
				lock.unlock();

				job->func(id, job->mem_ptr, job->mem_size);
				job->finished = true;
			}
			else
			{
				lock.unlock();
			}
		}
		goto start;
	}
}