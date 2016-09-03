#include "server.h"

#include "../console/console.h"
#include "../network/message_types.h"
#include <fstream>

#include <iostream>
#include <string>
#include <iostream>

namespace network
{
	//------------------------------------------------------------------------------------------------------
	Server::Server() :
		console_(nullptr)
	{

	}

	//------------------------------------------------------------------------------------------------------
	Server::~Server()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void Server::Initialise(console::Console* console)
	{
		console_ = console;

		console_->AddLog("Booting up server..");
		peer_ = RakNet::RakPeerInterface::GetInstance();

		RakNet::SocketDescriptor sd;
		
		peer_->Startup(1, &sd, 1);

		peer_->Connect("127.0.0.1", BB_CONSOLE_SERVER_PORT, 0, 0);

		bool connected = false;

		while (!connected)
		{
			RakNet::Packet* packet;

			bool unavailable = false;

			for (packet = peer_->Receive(); packet; peer_->DeallocatePacket(packet), packet = peer_->Receive())
			{
				switch (packet->data[0])
				{
				case ID_CONNECTION_REQUEST_ACCEPTED:
					connected = true;
					client_ = packet->systemAddress;
					break;
				default:
					unavailable = true;
					std::cout << "The console is unavailable: " << RakNet::PacketLogger::BaseIDTOString(packet->data[0]) << std::endl;
					break;
				}
			}

			if (unavailable)
			{
				break;
			}
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Server::Run()
	{
		if (console_ != nullptr || true)
		{
			qApp->processEvents();

			RakNet::Packet* packet;

			while (!console_->IsClosed())
			{	
				qApp->processEvents();
				for (packet = peer_->Receive(); packet; peer_->DeallocatePacket(packet), packet = peer_->Receive())
				{
					switch (packet->data[0])
					{
					case BB_CONSOLE_MESSAGE_TEXT_LOG:
						{
							RakNet::BitStream bit_stream(packet->data, packet->length, true);

							ConsoleMessageTextLog log;

							bit_stream.IgnoreBytes(sizeof(RakNet::MessageID));
							bit_stream.Read(log);

							console_->AddLog(log);
						}
						break;
					}
				}
			}

			RakNet::RakPeerInterface::DestroyInstance(peer_);
		}
	}
}