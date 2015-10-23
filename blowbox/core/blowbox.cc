#include "blowbox.h"

#include "../util/macros.h"
#include "../graphics/direct3d/renderer.h"

#include <iostream>

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Blowbox::Blowbox() :
		renderer_(nullptr)
	{

	}

	//------------------------------------------------------------------------------------------------------
	Blowbox::~Blowbox()
	{
		BB_SAFE_DELETE(renderer_);
	}

	//------------------------------------------------------------------------------------------------------
	void Blowbox::Run()
	{

	}
	
	//------------------------------------------------------------------------------------------------------
	void Blowbox::SetRenderer(direct3d::Renderer* renderer)
	{
		renderer_ = renderer;
	}
}