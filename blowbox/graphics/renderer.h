#pragma once

#include "../core/memory/memory_object.h"
#include "../graphics/direct3d.h"

using namespace blowbox::memory;

namespace blowbox
{
	class Renderer : public MObject
	{
	public:
		static Renderer* Create(Allocator* allocator);

		Renderer(Allocator* allocator);
		~Renderer();
	};
}