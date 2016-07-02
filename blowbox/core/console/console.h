#pragma once

#include <RakPeerInterface.h>
#include <BitStream.h>
#include <PacketLogger.h>
#include <MessageIdentifiers.h>
#include <iostream>

#include "../../core/memory/memory_object.h"
#include "../../core/console/message.h"

namespace RakNet
{
	class RakPeerInterface;
	struct SystemAddress;
}

namespace blowbox
{
	class Console : public memory::MObject
	{
	public:
		Console(memory::Allocator* allocator);
		~Console();

		static Console* Create(memory::Allocator* allocator);
		static Console* Instance();
		void Connect();
		void Disconnect();

		void Log(Message* message);
		void Log(const std::string& log, BB_MESSAGE_TYPES type);
	private:
		static Console* instance_;

		RakNet::RakPeerInterface* peer_;
		RakNet::SystemAddress server_;
		bool peer_started_;
		bool connection_attempt_started_;
		bool connected_;
	};
}