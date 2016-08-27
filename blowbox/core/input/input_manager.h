#pragma once

#include "../../core/memory/memory_object.h"

using namespace blowbox::memory;

namespace blowbox
{
	class InputManager : public MObject
	{
	public:
		static InputManager* Create(Allocator* allocator);
		static InputManager* Instance();

		InputManager(Allocator* allocator);
		~InputManager();

	private:
		static InputManager* instance_; //!< Singleton instance of InputManager
	};
}