//#include "task.h"
//
//#include <string>
//
//namespace blowbox
//{
//	void SumNumbersTask::DoWork(ITaskContext* context)
//	{
//		
//		Context* ctx = reinterpret_cast<Context*>(context); 
//		Console::Instance()->Log("Start summing for task id " + std::to_string(ctx->taskID), BB_MESSAGE_TYPE_LOG);
//		for (int i = 0; i < ctx->numbers.size(); i++)
//		{
//			ctx->result += ctx->numbers[i];
//		}
//		Console::Instance()->Log("Done summing for task id " + std::to_string(ctx->taskID) + ", sum is: " + std::to_string(ctx->result), BB_MESSAGE_TYPE_LOG);
//	}
//
//	void SumNumbersExitTask::DoWork(ITaskContext* context)
//	{
//		Context* ctx = reinterpret_cast<Context*>(context);
//
//		ctx->host->FinishedTasks();
//	};
//
//	SumNumbers::SumNumbers(const std::vector<unsigned long long>& numbers)
//	{
//		finished = false;
//		int task_count = 4;
//		int task_size = numbers.size() / task_count;
//
//		std::vector<SumNumbersTask*> tasks;
//		std::vector<SumNumbersTask::Context> contexts;
//
//		SumNumbersExitTask::Context exitTaskContext;
//		exitTaskContext.host = this;
//		SumNumbersExitTask* exitTask = new SumNumbersExitTask(&exitTaskContext);
//
//		/*for (int i = 0; i < task_count; i++)
//		{
//			SumNumbersTask::Context context;
//			Console::Instance()->Log(std::string("Task ") + std::to_string(i) + ": from " + std::to_string(i * task_size) + " to " + std::to_string((i + 1) * task_size), BB_MESSAGE_TYPE_ERROR);
//			context.numbers = std::vector<int>(numbers.begin() + i * task_size, numbers.begin() + (i + 1) * task_size);
//			context.result = 0;
//			contexts.push_back(context);
//
//			SumNumbersTask* task = new SumNumbersTask(&contexts[contexts.size() - 1]);
//			tasks.push_back(task);
//			TaskManager::Instance()->AddTask(task);
//			exitTask->AddDependency(task);
//		}*/
//
//		int i = 0;
//
//		SumNumbersTask::Context context0;
//		context0.numbers = std::vector<unsigned long long>(numbers.begin() + i * task_size, numbers.begin() + (i + 1) * task_size);
//		context0.result = 0;
//		context0.taskID = 0;
//		SumNumbersTask* task0 = new SumNumbersTask(&context0);
//		//Console::Instance()->Log(std::string("Task ") + std::to_string(i) + ": from " + std::to_string(i * task_size) + " to " + std::to_string((i + 1) * task_size), BB_MESSAGE_TYPE_ERROR);
//
//
//
//		i = 1;
//		SumNumbersTask::Context context1;
//		context1.numbers = std::vector<unsigned long long>(numbers.begin() + i * task_size, numbers.begin() + (i + 1) * task_size);
//		context1.result = 0;
//		context1.taskID = 1;
//		SumNumbersTask* task1 = new SumNumbersTask(&context1);
//		//Console::Instance()->Log(std::string("Task ") + std::to_string(i) + ": from " + std::to_string(i * task_size) + " to " + std::to_string((i + 1) * task_size), BB_MESSAGE_TYPE_ERROR);
//
//
//
//		i = 2;
//		SumNumbersTask::Context context2;
//		context2.numbers = std::vector<unsigned long long>(numbers.begin() + i * task_size, numbers.begin() + (i + 1) * task_size);
//		context2.result = 0;
//		SumNumbersTask* task2 = new SumNumbersTask(&context2);
//		//Console::Instance()->Log(std::string("Task ") + std::to_string(i) + ": from " + std::to_string(i * task_size) + " to " + std::to_string((i + 1) * task_size), BB_MESSAGE_TYPE_ERROR);
//
//
//
//		i = 3;
//		SumNumbersTask::Context context3;
//		context3.numbers = std::vector<unsigned long long>(numbers.begin() + i * task_size, numbers.begin() + (i + 1) * task_size);
//		context3.result = 0;
//		SumNumbersTask* task3 = new SumNumbersTask(&context3);
//		Console::Instance()->Log(std::string("Task ") + std::to_string(i) + ": from " + std::to_string(i * task_size) + " to " + std::to_string((i + 1) * task_size), BB_MESSAGE_TYPE_ERROR);
//
//
//		exitTask->AddDependency(task0);
//		exitTask->AddDependency(task1);
//		//exitTask->AddDependency(task2);
//		//exitTask->AddDependency(task3);
//
//		TaskManager::Instance()->AddTask(task0);
//		TaskManager::Instance()->AddTask(task1);
//		//TaskManager::Instance()->AddTask(task2);
//		//TaskManager::Instance()->AddTask(task3);
//		TaskManager::Instance()->AddTask(exitTask);
//
//		while (!finished) {}
//
//		Console::Instance()->Log("The result is: " + std::to_string(context0.result + context1.result + context2.result + context3.result), BB_MESSAGE_TYPE_LOG);
//	};
//
//	void SumNumbers::FinishedTasks()
//	{
//		finished = true;
//	}
//}