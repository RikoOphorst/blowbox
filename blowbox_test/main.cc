#include "blowbox/blowbox_include.h"

#include <iostream>
#include <string>
#include <vector>
#include <comdef.h>

#define BB_CONSOLE_SERVER_PORT 60000
#define BB_CONSOLE_MAX_CLIENTS 1

using namespace blowbox;
using namespace blowbox::direct3d;
using namespace blowbox::memory;

FreeListAllocator* allocator;
Console* console;

int main(int argc, char** argv)
{
	MemoryManager::Create();
	allocator = MemoryManager::Instance()->ConstructAllocator<FreeListAllocator>(sizeof(Console) * 10000);

	Blowbox* blowbox = Blowbox::Create(allocator);
	console = Console::Create(allocator);

	TaskManager* task_manager = TaskManager::Instance();
	task_manager->StartUp();

	std::vector<int> numbers;

	srand(time(0));

	for (int i = 0; i < 40000000; i++)
	{
		numbers.push_back(5);
	}

	SumNumbers* sum_numbers = new SumNumbers(numbers);

	std::cin.get();
	return 0;
}