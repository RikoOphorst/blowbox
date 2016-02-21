#include "console\console.h"
#include "network\client.h"

using namespace console;
using namespace network;

int main(int argc, char** argv)
{
	QApplication QApp(argc, argv);

	Console* console = new Console();

	Client* client = new Client();
	client->Initialise(console);

	return QApp.exec();
}