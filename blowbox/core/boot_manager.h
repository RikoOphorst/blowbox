#pragma once

#include "../../blowbox/core/cvar.h"
#include "../../blowbox/memory/memory.h"

namespace blowbox
{
	class BootManager
	{
	public:
		BootManager();
		~BootManager();

		void Boot(int argc, char** argv);
		void Shutdown();
	private:
		Memory* memory_;
		CVar* cvar_;
	};
}