#pragma once

#include "../core/memory/memory_object.h"

using namespace blowbox::memory;

namespace blowbox
{
	class Renderer : public MObject
	{
	public:
		static Renderer* Create(Allocator* allocator);

		Renderer();
		~Renderer();
	};
}