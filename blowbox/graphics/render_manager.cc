#include "render_manager.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	RenderManager::RenderManager()
	{

	}

	//------------------------------------------------------------------------------------------------------
	RenderManager::~RenderManager()
	{

	}

	//------------------------------------------------------------------------------------------------------
	RenderManager* RenderManager::Instance()
	{
		static RenderManager* ptr = Memory::Instance()->AllocateSingleton<RenderManager>();
		return ptr;
	}

	//------------------------------------------------------------------------------------------------------
	void RenderManager::StartUp()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void RenderManager::ShutDown()
	{

	}
}