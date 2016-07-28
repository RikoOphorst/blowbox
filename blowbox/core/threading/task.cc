#include "task.h"

namespace blowbox
{
	void SumNumbersTask::DoWork(ITaskContext* context)
	{
		Context* ctx = reinterpret_cast<Context*>(context);
		for (int i = 0; i < ctx->numbers.size(); i++)
		{
			ctx->result += ctx->numbers[i];
		}
	}

	void SumNumbersExitTask::DoWork(ITaskContext* context)
	{
		Context* ctx = reinterpret_cast<Context*>(context);

		ctx->host->FinishedTasks();
	};

	SumNumbers::SumNumbers(const std::vector<int>& numbers)
	{
		finished = false;
		int task_count = 4;
		int task_size = numbers.size() / task_count;

		std::vector<SumNumbersTask*> tasks;
		std::vector<SumNumbersTask::Context> contexts;

		SumNumbersExitTask::Context exitTaskContext;
		exitTaskContext.host = this;
		SumNumbersExitTask* exitTask = new SumNumbersExitTask(&exitTaskContext);

		for (int i = 0; i < task_count; i++)
		{
			SumNumbersTask::Context context;
			context.numbers = std::vector<int>(numbers.begin() + i * task_size, numbers.begin() + (i + 1) * task_size);
			context.result = 0;
			contexts.push_back(context);

			SumNumbersTask* task = new SumNumbersTask(&contexts[contexts.size() - 1]);
			tasks.push_back(task);
			TaskManager::Instance()->AddTask(task);
			exitTask->AddDependency(task);
		}

		TaskManager::Instance()->AddTask(exitTask);

		while (!finished) {}

		Console::Instance()->Log(std::to_string(contexts[0].result + contexts[1].result + contexts[2].result + contexts[3].result), BB_MESSAGE_TYPE_LOG);
	};

	void SumNumbers::FinishedTasks()
	{
		finished = true;
	}
}