#include "../blowbox/core/boot_manager.h"

#include "../blowbox/filesystem/file_system_manager.h"
#include "../blowbox/window/window_manager.h"

#include <iostream>

using namespace blowbox;

int main(int argc, char** argv)
{
	BootManager* boot_manager = new BootManager();
	boot_manager->Boot(argc, argv);

	Window* main1 = WindowManager::Instance()->MakeWindow("Blowbox - Main1", 1280, 720);
	Window* main2 = WindowManager::Instance()->MakeWindow("Blowbox - Main2", 1300, 720);
	Window* main3 = WindowManager::Instance()->MakeWindow("Blowbox - Main3", 1280, 740);

	while (true) {
		main1->ProcessMessages();
	}

	boot_manager->ShutDown();
	delete boot_manager;

	return 0;
}