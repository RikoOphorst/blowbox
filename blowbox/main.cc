#include "../blowbox/core/boot_sequence.h"
#include "../blowbox/window/window.h"

#include <iostream>

using namespace blowbox;

int main(int argc, char** argv)
{
	BootSequence* boot_sequence = new BootSequence();

	boot_sequence->Boot();

	Window* window = new Window("Blowbox", 1280, 720);
	
	while (true)
	{
		window->ProcessMessages();
	}

	boot_sequence->ShutDown();
	delete boot_sequence;

	return 0;
}