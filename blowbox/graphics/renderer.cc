#include "renderer.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Renderer* Renderer::Create(Allocator* allocator)
	{
		return MemoryManager::Allocate<Renderer>(allocator, allocator);
	}

	//------------------------------------------------------------------------------------------------------
	Renderer::Renderer(Allocator* allocator) :
		MObject(allocator)
	{

	}

	//------------------------------------------------------------------------------------------------------
	Renderer::~Renderer()
	{

	}
}