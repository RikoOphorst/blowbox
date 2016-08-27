#pragma once

#include <vector>
#include <functional>
#include <string>
#include "../../core/threading/task_manager.h"
#include "../../core/console/console.h"

namespace blowbox
{
	/**
	* @struct blowbox::TaskContext
	* @author Riko Ophorst
	* @brief Object that defines the context in which a task operates, i.e. the memory it can access freely without violating race conditions or things like that
	*/
	struct TaskContext {
		TaskContext()
		{
			task_name = "";
			task_id = task_id_accumulator++;
		}

		std::string task_name; //!< A task can have a name which will be stored here, in the task context
		int task_id; //!< A task always has an ID, which will be stored here, in the task context

		static unsigned int task_id_accumulator; //!< Acculumator value to generate unique ID's for every task context (and subsequently every task)
	};

	/**
	* @class blowbox::Task
	* @author Riko Ophorst
	* @brief A task is a wrapper around a code-routine which can operate on a given context
	*/
	class Task
	{
	public:
		/**
		* @brief Task constructor
		* @param[in]	context		The context in which this task will operate
		*/
		Task(TaskContext* context);

		~Task(); //!< Task destructor

		/**
		* @brief Execute this task
		*/
		void Execute();

		/**
		* @brief Are this task's dependencies finished?
		*/
		bool HasToWaitForDependencies();

		/**
		* @brief Force this task to wait until all its dependencies are finished
		*/
		void WaitForDependencies();

		/**
		* @brief Is this task finished?
		*/
		const bool& IsFinished() const;

		/**
		* @brief Add a dependency to this task
		* @param[in]	dependency	The task that this task should depend on
		*/
		void AddDependency(Task* dependency);

		/**
		* @brief Virtual function in which the actual meat of the task is implemented
		* @param[in]	context		The context in which the task operates
		*/
		virtual void DoWork(TaskContext* context) = 0;
		TaskContext* context_; //!< The context to this task

	private:
		std::vector<Task*> dependencies_; //!< The dependencies of this task
		bool is_finished_; //!< Is this task finished?
	};
}