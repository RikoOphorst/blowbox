#include "../blowbox/core/blowbox.h"
#include "../blowbox/window/window.h"
#include "../blowbox/graphics/direct3d/renderer.h"
#include <PxPhysicsAPI.h>

#include <iostream>

using namespace blowbox;
using namespace blowbox::direct3d;

int main(int argc, char** argv)
{	
	Blowbox* blowbox = new Blowbox();
	Window* window = Window::MakeWindow("My Blowbox Game", 1280, 720);
	Renderer* renderer = Renderer::MakeRenderer();
	
	renderer->SetWindow(window);
	blowbox->SetRenderer(renderer);

	blowbox->Run();

	delete blowbox;

	return 0;
}