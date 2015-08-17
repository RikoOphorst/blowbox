#include "boot_manager.h"

#include <iostream>

#include "../../blowbox/core/cvar.h"

namespace blowbox
{
	BootManager::BootManager()
	{

	}

	BootManager::~BootManager()
	{

	}

	void BootManager::Boot(int argc, char** argv)
	{
		CVar* cvar = CVar::Instance();
		cvar->Parse(argc, argv);
		CVar::Settings& settings = cvar->GetSettings();

		std::cout << settings.memory << std::endl;
	}
}