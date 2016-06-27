#include "console\console.h"
#include "network\server.h"

using namespace console;
using namespace network;

int main(int argc, char** argv)
{
	QApplication QApp(argc, argv);

	Console* console = new Console();

	Server* server = new Server();
	server->Initialise(console);

	server->Run();

	return QApp.exec();
}