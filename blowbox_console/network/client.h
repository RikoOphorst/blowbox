#pragma once

#include <winsock2.h>
#include <WS2tcpip.h>

namespace console
{
	class Console;
}

namespace network
{
	class Client
	{
	public:
		Client();
		~Client();

		void Initialise(console::Console* console);
	private:
		console::Console* console_;

		void InitWSA();
		void InitAddrInfo();
		void InitSocket();

		WSAData wsa_data_;
		addrinfo addr_hints_;
		addrinfo* addr_serv_info_;
		int sockfd_;
	};
}