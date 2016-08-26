#include "task.h"

namespace blowbox
{
	unsigned int TaskContext::task_id_accumulator = 0;
	
	//------------------------------------------------------------------------------------------------------
	Task::Task(TaskContext* context) :
		context_(context)
	{

	}

	//------------------------------------------------------------------------------------------------------
	Task::~Task()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void Task::Execute()
	{
		WaitForDependencies();

		DoWork(context_);

		is_finished_ = true;
	}
	
	//------------------------------------------------------------------------------------------------------
	bool Task::HasToWaitForDependencies()
	{
		for (int i = 0; i < dependencies_.size(); i++)
		{
			if (!dependencies_[i]->IsFinished())
			{
				return true;
			}
		}

		return false;
	}

	//------------------------------------------------------------------------------------------------------
	void Task::WaitForDependencies()
	{
		if (HasToWaitForDependencies())
		{
			Console::Instance()->Log("Waiting for dependencies..", BB_MESSAGE_TYPE_LOG);
		}
		else
		{
			return;
		}

		for (int i = 0; i < dependencies_.size(); i++)
		{
			while (!dependencies_[i]->IsFinished()) 
			{
				
			}
		}

		Console::Instance()->Log("Done waiting for dependencies.", BB_MESSAGE_TYPE_LOG);
	}
	
	//------------------------------------------------------------------------------------------------------
	void Task::AddDependency(Task* dependency)
	{
		dependencies_.push_back(dependency);
	}

	//------------------------------------------------------------------------------------------------------
	const bool& Task::IsFinished() const
	{
		return is_finished_;
	}
}