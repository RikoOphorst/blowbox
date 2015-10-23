#include "renderer.h"

#include "../../util/macros.h"
#include "../../window/window.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		Renderer* Renderer::MakeRenderer()
		{
			return new Renderer();
		}

		//------------------------------------------------------------------------------------------------------
		Renderer::Renderer() :
			window_(nullptr)
		{
			
		}

		//------------------------------------------------------------------------------------------------------
		Renderer::~Renderer()
		{
			BB_SAFE_DELETE(window_);
		}
		
		//------------------------------------------------------------------------------------------------------
		void Renderer::SetWindow(Window* window)
		{
			window_ = window;
		}
	}
}