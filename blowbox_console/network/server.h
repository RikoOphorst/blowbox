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
	private:
		console::Console* console_;

		RakNet::RakPeerInterface* peer_;
		RakNet::SystemAddress client_; //!< The client address of the application
	};
}