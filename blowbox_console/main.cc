#include "console\console.h"
#include "network\server.h"

using namespace console;
using namespace network;

int main(int argc, char** argv)
{
	QApplication QApp(argc, argv);

	Console* console = new Console();

	Server* client = new Server();
	client->Initialise(console);

	client->Run();

	return QApp.exec();
}

//#define MAX_CLIENTS 10
//#define SERVER_PORT 60000
//
//int main(void)
//{
//	char str[512];
//
//	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
//	bool isServer;
//	RakNet::Packet *packet;
//
//	RakNet::SocketDescriptor sd(SERVER_PORT, 0);
//	peer->Startup(MAX_CLIENTS, &sd, 1);
//	isServer = true;
//
//	printf("Starting the server.\n");
//	// We need to let the server accept incoming connections from the clients
//	peer->SetMaximumIncomingConnections(MAX_CLIENTS);
//
//	while (1)
//	{
//		for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
//		{
//			switch (packet->data[0])
//			{
//			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
//				printf("Another client has disconnected.\n");
//				break;
//			case ID_REMOTE_CONNECTION_LOST:
//				printf("Another client has lost the connection.\n");
//				break;
//			case ID_REMOTE_NEW_INCOMING_CONNECTION:
//				printf("Another client has connected.\n");
//				break;
//			case ID_CONNECTION_REQUEST_ACCEPTED:
//				printf("Our connection request has been accepted.\n");
//				break;
//			case ID_NEW_INCOMING_CONNECTION:
//				printf("A connection is incoming.\n");
//				break;
//			case ID_NO_FREE_INCOMING_CONNECTIONS:
//				printf("The server is full.\n");
//				break;
//			case ID_DISCONNECTION_NOTIFICATION:
//				if (isServer) {
//					printf("A client has disconnected.\n");
//				}
//				else {
//					printf("We have been disconnected.\n");
//				}
//				break;
//			case ID_CONNECTION_LOST:
//				if (isServer) {
//					printf("A client lost the connection.\n");
//				}
//				else {
//					printf("Connection lost.\n");
//				}
//				break;
//			default:
//				printf("Message with identifier %i has arrived.\n", packet->data[0]);
//				break;
//			}
//		}
//	}
//
//
//	RakNet::RakPeerInterface::DestroyInstance(peer);
//
//	return 0;
//}