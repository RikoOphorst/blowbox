#include "../blowbox/core/boot_manager.h"

using namespace blowbox;

int main(int argc, char** argv)
{
	BootManager* boot_manager = new BootManager();
	boot_manager->Boot(argc, argv);

	

	boot_manager->Shutdown();
	delete boot_manager;

	return 0;
}