#include "server.h"

#include "../console/console.h"

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

		//console_->AddLog("Booting up server..");
		peer_ = RakNet::RakPeerInterface::GetInstance();

		RakNet::SocketDescriptor sd(BB_CONSOLE_SERVER_PORT, 0);
		peer_->Startup(BB_CONSOLE_MAX_CLIENTS, &sd, 1);

		//console_->AddLog(std::string("Console listening on port ") + std::to_string(BB_CONSOLE_SERVER_PORT) + " for connections..");
		// We need to let the server accept incoming connections from the clients
		peer_->SetMaximumIncomingConnections(BB_CONSOLE_MAX_CLIENTS);
	}

	//------------------------------------------------------------------------------------------------------
	void Server::Run()
	{
		if (console_ != nullptr || true)
		{
			qApp->processEvents();

			RakNet::Packet* packet;

			bool exit = false;

			while (!console_->IsClosed())
			{	
				qApp->processEvents();
				for (packet = peer_->Receive(); packet; peer_->DeallocatePacket(packet), packet = peer_->Receive())
				{
					switch (packet->data[0])
					{
					case ID_NEW_INCOMING_CONNECTION:
					case ID_REMOTE_NEW_INCOMING_CONNECTION:
						console_->AddLog(std::string("New connection incoming: ") + packet->systemAddress.ToString());
						break;

					case ID_DISCONNECTION_NOTIFICATION:
					case ID_REMOTE_DISCONNECTION_NOTIFICATION:
						console_->AddLog(std::string("Console is disconnecting from: ") + packet->systemAddress.ToString());
						break;

					case ID_REMOTE_CONNECTION_LOST:
					case ID_CONNECTION_LOST:
						console_->AddLog(std::string("Connection to a client has been lost: ") + packet->systemAddress.ToString());
						break;

					case ID_NO_FREE_INCOMING_CONNECTIONS:
						console_->AddLog(std::string("A new connection was tried, but was not accepted because we are at the maximum amount of connections."));
						break;

					default:
						console_->AddLog(std::string("An unidentified message is coming in.."));
						break;
					}
				}
			}

			std::cout << "duuurp" << std::endl;
			RakNet::RakPeerInterface::DestroyInstance(peer_);
		}
	}
}