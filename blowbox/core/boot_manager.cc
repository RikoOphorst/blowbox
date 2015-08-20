#include "boot_manager.h"

#include <iostream>

#include "../../blowbox/filesystem/file_system_manager.h"
#include "../../blowbox/window/window_manager.h"
#include "../../blowbox/graphics/render_manager.h"

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

		FileSystemManager::Instance()->StartUp();
		WindowManager::Instance()->StartUp();
		RenderManager::Instance()->StartUp();
	}

	void BootManager::ShutDown()
	{
		RenderManager::Instance()->ShutDown();
		WindowManager::Instance()->ShutDown();
		FileSystemManager::Instance()->ShutDown();

		memory_->ShutDown();
		delete memory_;

		delete cvar_;
	}
}