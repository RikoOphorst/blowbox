#include <windows.h>
#include "../../../Server/HeapInspectorServer.h"
#include "../../../Server/PC_Windows/HeapHooks.h"

void RunHeapInspectorServer();

int main(int argc, char** argv)
{
	using namespace HeapInspectorServer;
	InitialiseHeapHooks();
	Initialise(3000, WaitForConnection_Enabled);
	SetHeapName(0, "test");

	RunHeapInspectorServer();

	Shutdown();
	ShutdownHeapHooks();
	return 0;
}
