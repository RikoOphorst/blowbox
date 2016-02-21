#include "client.h"

#include "../console/console.h"
#include <iostream>
#include <string>
#include <iostream>

void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

namespace network
{
	Client::Client()
	{

	}

	Client::~Client()
	{

	}

	void Client::Initialise(console::Console* console)
	{
		console_ = console;

		console_->AddLog("Initializing client...");

		InitWSA();
		InitAddrInfo();
		InitSocket();

		console_->AddLog("Initialized client.");
		console_->AddLog("Binding to port 6432...");

		char yes = 1;
		if (setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		{
			console_->AddLog("Failed bind on port 6432: ");
		}

		int bind_res = bind(sockfd_, addr_serv_info_->ai_addr, addr_serv_info_->ai_addrlen);

		if (bind_res == -1)
		{
			console_->AddLog("Failed bind on port 6432: ");
		}

		console_->AddLog("Bound to port 6432.");

		if (listen(sockfd_, 10) == -1)
		{
			console_->AddLog("Failed to start listening on port 6432");
		}
		console_->AddLog("Listening on port 6432.");

		sockaddr_storage their_addr;
		socklen_t sin_size;
		int new_fd = -1;
		char string[INET6_ADDRSTRLEN];

		console_->AddLog("Waiting for connections...");


		qApp->processEvents();
		while (true)
		{
			qApp->processEvents();
			std::cout << "no connection.." << std::endl;

			sin_size = sizeof(their_addr);
			new_fd = accept(sockfd_, (sockaddr*)&their_addr, &sin_size);

			if (new_fd == -1)
			{
				console_->AddLog("No connection");
				continue;
			}

			inet_ntop(their_addr.ss_family, get_in_addr((sockaddr*)&their_addr), string, sizeof(string));
			printf("server: got connection from %s\n", string);

			break;
		}

		console_->AddLog("waiting for messages");
		while (true)
		{
			qApp->processEvents();
			char* msg = "";
			int num_bytes = recv(sockfd_, msg, 14, 0);

			if (num_bytes != -1)
			{
				std::cout << "erm" << std::endl;

				break;
			}
			else
			{
				num_bytes = recv(new_fd, msg, 14, 0);

				if (num_bytes != -1)
				{
					std::cout << "erm" << std::endl;
				}
			}
		}
	}

	void Client::InitWSA()
	{
		console_->AddLog("Initializing WSA data...");
		WSADATA wsaData;

		MAKEWORD(2, 0);

		if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
		{
			console_->AddLog("Failed initializing WSA data.");
			exit(1);
		}

		console_->AddLog("Initialized WSA data.");
	}

	void Client::InitAddrInfo()
	{
		console_->AddLog("Initializing address info...");

		int status;

		memset(&addr_hints_, 0, sizeof(addr_hints_));
		addr_hints_.ai_family = AF_UNSPEC;
		addr_hints_.ai_socktype = SOCK_STREAM;

		if ((status = getaddrinfo("127.0.0.1", "6432", &addr_hints_, &addr_serv_info_)) != 0)
		{
			console_->AddLog("Failed initializing address info: " + std::string(gai_strerror(status)));
			exit(1);
		}

		console_->AddLog("Initialized address info.");
	}

	void Client::InitSocket()
	{
		console_->AddLog("Initializing socket...");
		sockfd_ = socket(addr_serv_info_->ai_family, addr_serv_info_->ai_socktype, addr_serv_info_->ai_protocol);

		if (sockfd_ == -1)
		{
			console_->AddLog("Failed initializing socket: ");
			exit(1);
		}

		console_->AddLog("Initialized socket.");
	}
}