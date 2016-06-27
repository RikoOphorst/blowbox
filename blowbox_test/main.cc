#include <RakPeerInterface.h>
#include <BitStream.h>
#include <PacketLogger.h>
#include <MessageIdentifiers.h>

#include "blowbox/blowbox_include.h"

#include <iostream>
#include <string>
#include <vector>

#define BB_CONSOLE_SERVER_PORT 60000
#define BB_CONSOLE_MAX_CLIENTS 1

using namespace blowbox;
using namespace blowbox::direct3d;
using namespace blowbox::memory;

int main(int argc, char** argv)
{
	//#ifdef HEAP_INSPECTOR_ENABLED
	//	HeapInspectorServer::InitialiseHeapHooks();
	//	HeapInspectorServer::Initialise(3000, HeapInspectorServer::WaitForConnection_Enabled);
	//	HeapInspectorServer::SetHeapName(0, "blowbox_main");
	//#endif

	/*RakNet::RakPeerInterface* peer = RakNet::RakPeerInterface::GetInstance();

	RakNet::Packet* packet = NULL;
	RakNet::SocketDescriptor sd;

	RakNet::StartupResult result = peer->Startup(1, &sd, 1);

	RakNet::ConnectionAttemptResult result2 = peer->Connect("127.0.0.1", BB_CONSOLE_SERVER_PORT, 0, 0);

	RakNet::SystemAddress serverAddress;

	bool exit = false;

	while (!exit)
	{
		for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
		{
			switch (packet->data[0])
			{
			case ID_CONNECTION_REQUEST_ACCEPTED:
				std::cout << "The console has accepted our request" << std::endl;
				break;
			case ID_DISCONNECTION_NOTIFICATION:
			case ID_REMOTE_CONNECTION_LOST:
			case ID_CONNECTION_LOST:
				std::cout << "The connection is disconnected" << std::endl;
				break;
			default:
				std::cout << "Unidentified message: " << (int)packet->data[0] << "\t";
				if (packet->data[0] < ID_USER_PACKET_ENUM)
				{
					std::cout << RakNet::PacketLogger::BaseIDTOString(packet->data[0]) << std::endl;
				}
				else
				{
					std::cout << "Custom packet" << std::endl;
				}
				break;
			}
		}
	}*/

	/*Blowbox* blowbox = Blowbox::Create();
	Window* window = Window::MakeWindow("blowbox", 800, 600);
	Renderer* renderer = Renderer::Create();
	blowbox->SetWindow(window);
	blowbox->SetRenderer(renderer);

	Camera* camera = Camera::Create(BB_CAMERA_PROJECTION_MODES::BB_CAMERA_PROJECTION_MODE_PERSPECTIVE);

	renderer->SetWindow(window);
	renderer->SetCamera(camera);

	blowbox->Initialise();

	blowbox->Run();

	std::cin.get();*/

//#ifdef HEAP_INSPECTOR_ENABLED
//	HeapInspectorServer::Shutdown();
//	HeapInspectorServer::ShutdownHeapHooks();
//#endif
	return 0;
}