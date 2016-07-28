#pragma once

#include <vector>
#include <functional>
#include <string>
#include "../../core/threading/task_manager.h"
#include "../../core/console/console.h"

namespace blowbox
{
	struct ITaskContext {};

	class Task
	{
	public:
		Task(ITaskContext* context) : context_(context) {};
		~Task() {};

		const bool& IsFinished() const
		{
			return is_finished_;
		}

		void WaitForDependencies()
		{
			for (int i = 0; i < dependencies_.size(); i++)
			{
				while (!dependencies_[i]->IsFinished()) {}
			}
		};

		void Execute()
		{
			WaitForDependencies();

			DoWork(context_);

			is_finished_ = true;
		};

		void AddDependency(Task* dependency)
		{
			dependencies_.push_back(dependency);
		}

		virtual void DoWork(ITaskContext* context) = 0;

	private:
		ITaskContext* context_;
		std::vector<Task*> dependencies_;
		bool is_finished_;
	};

	class SumNumbers
	{
	public:
		SumNumbers(const std::vector<int>& numbers);

		void FinishedTasks();
	private:
		int result;
		bool finished;
	};
	
	class SumNumbersTask : public Task
	{
	public:
		struct Context : public ITaskContext
		{
			~Context() {
				int i = 0;
			};

			std::vector<int> numbers;
			int result;
		};

		SumNumbersTask(Context* context) : Task(context) {};

		void DoWork(ITaskContext* context);
	}; 
	
	class SumNumbersExitTask : public Task
	{
	public:

		struct Context : public ITaskContext
		{
			SumNumbers* host;
		};

		SumNumbersExitTask(Context* context) : Task(context) {};

		void DoWork(ITaskContext* context);
	}; 
}