#include "blowbox.h"

#include "../core/game_object.h"
#include "../util/macros.h"
#include "../graphics/direct3d/renderer.h"
#include "../window/window.h"

#include <iostream>

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Blowbox::Blowbox() :
		renderer_(nullptr),
		can_run_(false),
		running_(false)
	{

	}
	
	//------------------------------------------------------------------------------------------------------
	Blowbox::~Blowbox()
	{
		BB_SAFE_DELETE(renderer_);
	}

	//------------------------------------------------------------------------------------------------------
	Blowbox* Blowbox::Create()
	{
		return new Blowbox();
	}

	//------------------------------------------------------------------------------------------------------
	void Blowbox::Initialise()
	{
		BB_ASSERT_NOTNULL(renderer_, "A renderer has to be set in order to initialise Blowbox. Use Blowbox::SetRenderer() to set a renderer.");

		renderer_->Initialise(window_);

		can_run_ = true;
	}

	//------------------------------------------------------------------------------------------------------
	void Blowbox::Run()
	{
		BB_ASSERT(can_run_, "Blowbox has to be initialised before it can be run. Use Blowbox::Initialise() to initialise Blowbox.");

		running_ = true;

		while (running_)
		{
			renderer_->Draw(game_objects_);
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Blowbox::SetRenderer(direct3d::Renderer* renderer)
	{
		renderer_ = renderer;
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