#include "console.h"

#include <iostream>

#define BB_CONSOLE_SERVER_PORT 60000

namespace blowbox
{
	Console* Console::instance_ = nullptr;
	
	//------------------------------------------------------------------------------------------------------
	Console::Console(memory::Allocator* allocator) :
		MObject(allocator),
		peer_(nullptr),
		connection_attempt_started_(false),
		peer_started_(false),
		connected_(false)
	{
		Connect();
	}

	//------------------------------------------------------------------------------------------------------
	Console::~Console()
	{

	}

	//------------------------------------------------------------------------------------------------------
	Console* Console::Create(memory::Allocator* allocator)
	{
		return instance_ = memory::MemoryManager::Allocate<Console>(allocator, allocator);
	}

	//------------------------------------------------------------------------------------------------------
	Console* Console::Instance()
	{
		return instance_;
	}

	//------------------------------------------------------------------------------------------------------
	void Console::Connect()
	{
		if (connected_)
			Disconnect();

		peer_ = RakNet::RakPeerInterface::GetInstance();

		RakNet::SocketDescriptor sd;

		peer_started_ = false;
		connection_attempt_started_ = false;
		connected_ = false;

		if (peer_->Startup(1, &sd, 1) == RakNet::StartupResult::RAKNET_STARTED)
		{
			peer_started_ = true;

			if (peer_->Connect("127.0.0.1", BB_CONSOLE_SERVER_PORT, 0, 0) == RakNet::ConnectionAttemptResult::CONNECTION_ATTEMPT_STARTED)
			{
				connection_attempt_started_ = true;
			}
		}

		while (!connected_)
		{
			RakNet::Packet* packet;

			bool unavailable = false;

			for (packet = peer_->Receive(); packet; peer_->DeallocatePacket(packet), packet = peer_->Receive())
			{
				switch (packet->data[0])
				{
				case ID_CONNECTION_REQUEST_ACCEPTED:
					connected_ = true;
					server_ = packet->systemAddress;
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
	void Console::Disconnect()
	{
		if (peer_ != nullptr)
		{
			connected_ = false;
			connection_attempt_started_ = false;
			peer_started_ = false;

			peer_->CloseConnection(server_, true);

			peer_ = nullptr;
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Console::Log(Message* message)
	{
		if (connected_)
		{
			RakNet::BitStream bit_stream;
			bit_stream.Write((RakNet::MessageID)BB_CONSOLE_MESSAGE_TEXT_LOG);
			bit_stream.Write(message->GetActualMessage());
			peer_->Send(&bit_stream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, server_, false);
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Console::Log(const std::string& log, BB_MESSAGE_TYPES message_type)
	{
		Message* message = Message::Create(allocator_, log, message_type);
		Log(message);
		memory::MemoryManager::Deallocate(allocator_, message);
	}
}