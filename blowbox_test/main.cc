#include "blowbox/blowbox_include.h"

#include <iostream>
#include <string>

using namespace blowbox;
using namespace blowbox::direct3d;
using namespace blowbox::memory;

int main(int argc, char** argv)
{
#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Initialise(3000, HeapInspectorServer::WaitForConnection_Enabled);
	HeapInspectorServer::SetHeapName(0, "blowbox_main");
#endif

	Blowbox* blowbox = Blowbox::Create();
	Window* window = Window::MakeWindow("blowbox", 800, 600);
	Renderer* renderer = Renderer::Create();
	blowbox->SetWindow(window);
	blowbox->SetRenderer(renderer);

	Camera* camera = Camera::Create(BB_CAMERA_PROJECTION_MODES::BB_CAMERA_PROJECTION_MODE_PERSPECTIVE);

	renderer->SetWindow(window);
	renderer->SetCamera(camera);

	blowbox->Initialise();

	blowbox->Run();

	std::cin.get();

#ifdef HEAP_INSPECTOR_ENABLED
	HeapInspectorServer::Shutdown();
#endif
	return 0;
}