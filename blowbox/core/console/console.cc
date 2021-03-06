#include "console.h"

#include <RakPeerInterface.h>
#include <BitStream.h>
#include <PacketLogger.h>
#include <MessageIdentifiers.h>

#include <iostream>

#define BB_CONSOLE_SERVER_PORT 60000
#define BB_CONSOLE_MAX_CLIENTS 1

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
		temp_message_allocator_ = MemoryManager::LinearAllocator(10000);

		Connect();
	}

	//------------------------------------------------------------------------------------------------------
	Console::~Console()
	{
		Disconnect();
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

		RakNet::SocketDescriptor sd(BB_CONSOLE_SERVER_PORT, 0);
		peer_->Startup(BB_CONSOLE_MAX_CLIENTS, &sd, 1); 
		peer_->SetMaximumIncomingConnections(BB_CONSOLE_MAX_CLIENTS);

		peer_started_ = true;
		connected_ = false;

		while (!connected_)
		{
			for (auto packet = peer_->Receive(); packet; peer_->DeallocatePacket(packet), packet = peer_->Receive())
			{
				switch (packet->data[0])
				{
				case ID_NEW_INCOMING_CONNECTION:
				case ID_REMOTE_NEW_INCOMING_CONNECTION:
					connected_ = true;
					client_ = packet->systemAddress;
					break;

				case ID_DISCONNECTION_NOTIFICATION:
				case ID_REMOTE_DISCONNECTION_NOTIFICATION:
					connected_ = false;
					client_ = NULL;
					break;

				case ID_REMOTE_CONNECTION_LOST:
				case ID_CONNECTION_LOST:
					connected_ = false;
					client_ = NULL;
					break;
				}
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

			peer_->CloseConnection(client_, true, 0, PacketPriority::IMMEDIATE_PRIORITY);

			peer_ = nullptr;
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Console::Update()
	{
		if (!connected_)
		{
			for (auto packet = peer_->Receive(); packet; peer_->DeallocatePacket(packet), packet = peer_->Receive())
			{
				switch (packet->data[0])
				{
				case ID_NEW_INCOMING_CONNECTION:
				case ID_REMOTE_NEW_INCOMING_CONNECTION:
					connected_ = true;
					client_ = packet->systemAddress;
					break;

				case ID_DISCONNECTION_NOTIFICATION:
				case ID_REMOTE_DISCONNECTION_NOTIFICATION:
					connected_ = false;
					client_ = NULL;
					break;

				case ID_REMOTE_CONNECTION_LOST:
				case ID_CONNECTION_LOST:
					connected_ = false;
					client_ = NULL;
					break;
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Console::Log(Message* message, bool wait_for_ack)
	{
		if (connected_)
		{
			RakNet::BitStream bit_stream;
			bit_stream.Write(static_cast<RakNet::MessageID>(BB_CONSOLE_MESSAGE_TEXT_LOG));
			bit_stream.Write(message->GetActualMessage());
			peer_->Send(&bit_stream, IMMEDIATE_PRIORITY, wait_for_ack ? RELIABLE_ORDERED_WITH_ACK_RECEIPT : RELIABLE_ORDERED, 0, client_, false);

			if (wait_for_ack)
			{
				bool received = false;
				while (!received)
				{
					for (auto packet = peer_->Receive(); packet; peer_->DeallocatePacket(packet), packet = peer_->Receive())
					{
						switch (packet->data[0])
						{
						case ID_SND_RECEIPT_ACKED:
							received = true;
							break;
						}
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------------
	void Console::Log(const std::string& log, BB_MESSAGE_TYPES message_type, bool wait_for_ack)
	{
		Message* message = Message::Create(temp_message_allocator_, log, message_type);
		Log(message, wait_for_ack);
		temp_message_allocator_->Reset();
	}
	
	//------------------------------------------------------------------------------------------------------
	void Console::Log(const std::basic_ostream<char, std::char_traits<char>>& log, BB_MESSAGE_TYPES message_type, bool wait_for_ack)
	{
		std::stringstream ss;
		ss << log.rdbuf();

		Message* message = Message::Create(temp_message_allocator_, ss.str(), message_type);
		Log(message, wait_for_ack);
		temp_message_allocator_->Reset();
	}
}