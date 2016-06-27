#pragma once

#include <RakPeerInterface.h>
#include <BitStream.h>
#include <PacketLogger.h>
#include <MessageIdentifiers.h>

#define BB_CONSOLE_SERVER_PORT 60000
#define BB_CONSOLE_MAX_CLIENTS 10

namespace console
{
	class Console;
}

namespace network
{
	class Server
	{
	public:
		Server();
		~Server();

		void Initialise(console::Console* console);

		void Run();

		void Update();
	private:
		console::Console* console_;

		RakNet::RakPeerInterface* peer_;
	};
}