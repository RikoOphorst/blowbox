#include "input_manager.h"

#include "../../window/window.h"

namespace blowbox
{
	InputManager* InputManager::instance_ = nullptr;

	//------------------------------------------------------------------------------------------------------
	InputManager* InputManager::Create(Allocator* allocator, Window* input_window)
	{
		return instance_ = MemoryManager::Allocate<InputManager>(allocator, allocator, input_window);
	}

	//------------------------------------------------------------------------------------------------------
	InputManager* InputManager::Instance()
	{
		return instance_;
	}

	//------------------------------------------------------------------------------------------------------
	InputManager::InputManager(Allocator* allocator, Window* input_window) :
		MObject(allocator),
		input_window_(input_window)
	{
		//input_window_->
	}

	//------------------------------------------------------------------------------------------------------
	InputManager::~InputManager()
	{

	}
}