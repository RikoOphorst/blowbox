#pragma once

#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>

namespace blowbox
{
	struct Job;
	
	class JobManager
	{
	public:
		JobManager();
		~JobManager();

		static JobManager* Instance();

	private:
		std::queue<Job> jobs_;
	};
}