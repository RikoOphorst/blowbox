#include "blowbox/blowbox_include.h"

using namespace blowbox;
using namespace blowbox::direct3d;

int main(int argc, char** argv)
{
	Blowbox* blowbox = new Blowbox();

	Renderer* renderer = Renderer::Create();
	blowbox->SetRenderer(renderer);

	Window* window = Window::MakeWindow("A blowbox game", 1280, 720);
	renderer->SetWindow(window);

	renderer->Initialise();
	
	blowbox->Run();
	
	return 0;
}