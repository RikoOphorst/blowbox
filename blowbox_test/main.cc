//#include "blowbox/blowbox_include.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <WinSock2.h>
#include <WS2tcpip.h>

//using namespace blowbox;
//using namespace blowbox::direct3d;
//using namespace blowbox::memory;

int main(int argc, char** argv)
{
//#ifdef HEAP_INSPECTOR_ENABLED
//	HeapInspectorServer::InitialiseHeapHooks();
//	HeapInspectorServer::Initialise(3000, HeapInspectorServer::WaitForConnection_Enabled);
//	HeapInspectorServer::SetHeapName(0, "blowbox_main");
//#endif

	WSADATA wsaData;

	MAKEWORD(2, 0);

	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
	{
		exit(1);
	}

	int status;

	addrinfo addr_hints_;
	addrinfo* addr_serv_info_;

	memset(&addr_hints_, 0, sizeof(addr_hints_));
	addr_hints_.ai_family = AF_UNSPEC;
	addr_hints_.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo("127.0.0.1", "6432", &addr_hints_, &addr_serv_info_)) != 0)
	{
		exit(2);
	}

	int sockfd_ = socket(addr_serv_info_->ai_family, addr_serv_info_->ai_socktype, addr_serv_info_->ai_protocol);

	if (sockfd_ == -1)
	{
		exit(3);
	}

	while (1)
	{
		std::cout << "Connecting to client..." << std::endl;
		if (connect(sockfd_, addr_serv_info_->ai_addr, addr_serv_info_->ai_addrlen) != -1)
		{
			sockaddr_in* in = (sockaddr_in*)addr_serv_info_->ai_addr;
			char ip[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(in->sin_addr), ip, INET_ADDRSTRLEN);
			std::cout << "Connected to " << ip << std::endl;
			break;
		}
	}

	sockaddr_storage their_addr;

	for (int i = 0; i < 100; i++)
	{
		int bytes_send = send(sockfd_, "Hello, world!\0", 14, 0); 
		char err[200];
		strerror_s(err, 200, errno);
		printf("Error: %s", err);
		printf(" Bytes send: %i\n", bytes_send);
	}

	closesocket(sockfd_);

	WSACleanup();

	std::cin.get();

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