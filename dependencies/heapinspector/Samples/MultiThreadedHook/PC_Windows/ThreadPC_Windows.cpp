#include <windows.h>
#include "../IThread.h"

DWORD WINAPI InternalThread(LPVOID lpParam)
{
	ThreadFunction function = (ThreadFunction)lpParam;
	function();

	return 0;
}

class ThreadPC_Windows : public IThread
{
public:
	virtual void Fork(ThreadFunction a_Function)
	{
		m_Thread = CreateThread(NULL, 0, InternalThread, a_Function, 0, 0);
	}

	virtual void Join()
	{
		WaitForSingleObject(m_Thread, INFINITE);
	}

private:
	HANDLE m_Thread;
};


IThread* CreateThread()
{
	return new ThreadPC_Windows();
}

void DestroyThread(IThread* a_Thread)
{
	delete a_Thread;
}