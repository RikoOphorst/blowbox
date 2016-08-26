#pragma once

#include "blowbox/blowbox_include.h"
#include "blowbox/core/threading/task.h"

using namespace blowbox;
using namespace blowbox::memory;

class SumNumbersTask : public Task
{
public:
	struct Context : TaskContext
	{
		std::vector<unsigned long long> numbers;
		unsigned long long result;
	};

	SumNumbersTask(Context* context) :
		Task(context)
	{};

	void DoWork(TaskContext* context) override
	{
		Context* ctx = reinterpret_cast<Context*>(context);

		for (int i = 0; i < ctx->numbers.size(); i++)
		{
			for (int j = 0; j < ctx->numbers.size(); j++)
			{
				ctx->result += sqrt(ctx->numbers[j]);
			}

			ctx->result += sqrt(ctx->numbers[i]);
		}
	};
};

class SumNumbersExitTask : public Task
{
public:
	struct Context : TaskContext
	{
		std::mutex* finished_mutex;
		bool* finished;
	};

	SumNumbersExitTask(Context* context) :
		Task(context)
	{};

	void DoWork(TaskContext* context) override
	{
		Context* ctx = reinterpret_cast<Context*>(context);

		{
			std::lock_guard<std::mutex> lck(*ctx->finished_mutex);
			*ctx->finished = true;
		}
	};
};