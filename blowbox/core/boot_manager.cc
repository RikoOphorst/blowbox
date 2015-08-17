#include "boot_manager.h"

#include <iostream>

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
		cvar_ = CVar::Instance();
		cvar_->Parse(argc, argv);
		CVar::Settings& settings = cvar_->GetSettings();

		memory_ = Memory::Instance();
		memory_->StartUp(settings.memory);

		
	}

	void BootManager::Shutdown()
	{
		memory_->Shutdown();
		delete memory_;

		delete cvar_;
	}
}