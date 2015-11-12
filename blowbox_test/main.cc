#include "blowbox/blowbox_include.h"

using namespace blowbox;
using namespace blowbox::direct3d;

int main(int argc, char** argv)
{
	Blowbox* blowbox = Blowbox::Create();

	Window* window = Window::MakeWindow("A blowbox game", 1280, 720);

	Renderer* renderer = Renderer::Create();
	
	blowbox->SetWindow(window);
	blowbox->SetRenderer(renderer);

	blowbox->Initialise();

	GameObject* player = GameObject::Create();

	blowbox->Run();

	delete blowbox;

	return 0;
}