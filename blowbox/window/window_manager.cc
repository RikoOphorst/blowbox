#include "window_manager.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	WindowManager::WindowManager()
	{

	}

	//------------------------------------------------------------------------------------------------------
	WindowManager::~WindowManager()
	{

	}

	//------------------------------------------------------------------------------------------------------
	WindowManager* WindowManager::Instance()
	{
		static WindowManager* ptr = Memory::Instance()->AllocateSingleton<WindowManager>();
		return ptr;
	}

	//------------------------------------------------------------------------------------------------------
	void WindowManager::StartUp()
	{
		windows_ = Memory::Instance()->CreatePoolAllocator<Window>(sizeof(Window) * 50);
	}

	//------------------------------------------------------------------------------------------------------
	void WindowManager::ShutDown()
	{

	}

	//------------------------------------------------------------------------------------------------------
	Window* WindowManager::MakeWindow(const std::string& name, unsigned int width, unsigned int height)
	{
		Window* window = Memory::Instance()->Allocate<Window, const std::string&, unsigned int, unsigned int>(windows_, name, width, height);

		return window;
	}
}