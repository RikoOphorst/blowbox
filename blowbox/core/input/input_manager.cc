#include "input_manager.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	InputManager* InputManager::Create(Allocator* allocator)
	{
		return instance_ = MemoryManager::Allocate<InputManager>(allocator, allocator);
	}

	//------------------------------------------------------------------------------------------------------
	InputManager* InputManager::Instance()
	{
		return instance_;
	}

	//------------------------------------------------------------------------------------------------------
	InputManager::InputManager(Allocator* allocator) :
		MObject(allocator)
	{
		
	}

	//------------------------------------------------------------------------------------------------------
	InputManager::~InputManager()
	{

	}
}