//#pragma once
//
//#include <thread>
//#include <mutex>
//#include <condition_variable>
//
//namespace blowbox
//{
//	class WorkerThread
//	{
//	public:
//		WorkerThread(int id);
//		~WorkerThread();
//
//		static WorkerThread* MakeWorkerThread(int id);
//		static void ThreadFunction(int id);
//	private:
//
//		std::thread thread_;
//	};
//}