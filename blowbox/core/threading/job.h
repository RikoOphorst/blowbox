#pragma once

#include <vector>
#include <functional>

namespace blowbox
{
	struct Job
	{
		Job() {};

		Job(void(*func)(int, void*, int), void* mem_ptr, int mem_size, std::vector<Job*> others = {}) :
			func(func),
			mem_ptr(mem_ptr),
			mem_size(mem_size),
			finished(false), 
			others(others) 
		{

		};

		void(*func)(int, void*, int);
		bool finished;
		std::vector<Job*> others;
		void* mem_ptr;
		int mem_size;
	};
}