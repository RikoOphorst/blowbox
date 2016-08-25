#include "blowbox.h"

#include "../util/macros.h"
#include "../core/console/console.h"
#include "../window/window.h"
#include "../graphics/renderer.h"
#include "../core/game_object.h"


#include <iostream>

using namespace blowbox::memory;

namespace blowbox
{
	bool Blowbox::blowbox_created_ = false;

	//------------------------------------------------------------------------------------------------------
	Blowbox::Blowbox(memory::Allocator* allocator) :
		MObject(allocator),
		can_run_(false),
		running_(false)
	{

	}
	
	//------------------------------------------------------------------------------------------------------
	Blowbox::~Blowbox()
	{
		
	}

	//------------------------------------------------------------------------------------------------------
	Blowbox* Blowbox::Create()
	{
		if (!blowbox_created_)
		{
			MemoryManager::Create();
			StackAllocator* allocator = MemoryManager::StackAllocator(100);

			blowbox_created_ = true;

			return MemoryManager::Allocate<Blowbox>(allocator, allocator);
		}
		else
		{
			BB_BREAK("A try was made to create a Blowbox instance while there already exists one.");
			return nullptr;
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Blowbox::Initialise()
	{
		subsystem_allocator_ = MemoryManager::StackAllocator(2000);

		console_ = Console::Create(subsystem_allocator_);
		window_ = Window::Create(subsystem_allocator_, "blowbox", 1280, 720);

		can_run_ = true;
	}

	//------------------------------------------------------------------------------------------------------
	void Blowbox::Shutdown()
	{
		MemoryManager::Deallocate(subsystem_allocator_, window_);
		MemoryManager::Deallocate(subsystem_allocator_, console_);

		MemoryManager::Instance()->DestructAllocator(subsystem_allocator_);
	}

	//------------------------------------------------------------------------------------------------------
	void Blowbox::Run()
	{
		BB_ASSERT(can_run_, "Blowbox has to be initialised before it can be run. Use Blowbox::Initialise() to initialise Blowbox.");

		running_ = true;

		while (running_)
		{
			window_->ProcessMessages();
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Blowbox::SetWindow(Window* window)
	{
		window_ = window;
	}
}