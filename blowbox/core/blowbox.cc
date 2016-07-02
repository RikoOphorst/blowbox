#include "blowbox.h"

#include "../window/window.h"
#include "../core/console/console.h"
#include "../core/game_object.h"

#include <iostream>

namespace blowbox
{
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
	Blowbox* Blowbox::Create(memory::Allocator* allocator)
	{
		return memory::MemoryManager::Allocate<Blowbox>(allocator, allocator);
	}

	//------------------------------------------------------------------------------------------------------
	void Blowbox::Initialise()
	{
		//BB_ASSERT_NOTNULL(renderer_, "A renderer has to be set in order to initialise Blowbox. Use Blowbox::SetRenderer() to set a renderer.");

		can_run_ = true;
	}

	//------------------------------------------------------------------------------------------------------
	void Blowbox::Run()
	{
		//BB_ASSERT(can_run_, "Blowbox has to be initialised before it can be run. Use Blowbox::Initialise() to initialise Blowbox.");

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
	
	//------------------------------------------------------------------------------------------------------
	void Blowbox::AddGameObject(GameObject* game_object)
	{
		game_objects_.push_back(game_object);
	}
}