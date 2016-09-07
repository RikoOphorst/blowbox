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

		console_->AddLog("Booting up client..");
		peer_ = RakNet::RakPeerInterface::GetInstance();

		RakNet::SocketDescriptor sd;
		
		peer_->Startup(1, &sd, 1);

		peer_->Connect("127.0.0.1", BB_CONSOLE_SERVER_PORT, 0, 0);

		connected_ = false;
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

				if (connected_ == false)
				{
					peer_->Connect("127.0.0.1", BB_CONSOLE_SERVER_PORT, 0, 0);
				}

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
					case ID_CONNECTION_REQUEST_ACCEPTED:
						connected_ = true;
						client_ = packet->systemAddress;

						console_->AddLog("New blowbox found.");
						break;
					case ID_CONNECTION_LOST:
					case ID_DISCONNECTION_NOTIFICATION:
					case ID_REMOTE_CONNECTION_LOST:
					case ID_REMOTE_DISCONNECTION_NOTIFICATION:
						connected_ = false;
						client_ = packet->systemAddress;
						console_->AddLog("blowbox connection lost.");
						break;
					}
				}
			}

			RakNet::RakPeerInterface::DestroyInstance(peer_);
		}
	}
}