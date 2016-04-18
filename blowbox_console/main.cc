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