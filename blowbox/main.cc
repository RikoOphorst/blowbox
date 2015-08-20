#include "../blowbox/core/boot_manager.h"

#include "../blowbox/filesystem/file_system_manager.h"
#include "../blowbox/window/window_manager.h"

#include <iostream>

using namespace blowbox;

int main(int argc, char** argv)
{
	BootManager* boot_manager = new BootManager();
	boot_manager->Boot(argc, argv);

	WindowManager::Instance()->MakeWindow("derp", 100, 100);

	while (true) {}

	boot_manager->ShutDown();
	delete boot_manager;

	return 0;
}