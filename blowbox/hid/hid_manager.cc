#include "hid_manager.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	HIDManager::HIDManager()
	{

	}

	//------------------------------------------------------------------------------------------------------
	HIDManager::~HIDManager()
	{

	}

	//------------------------------------------------------------------------------------------------------
	HIDManager* HIDManager::Instance()
	{
		static HIDManager* ptr = Memory::Instance()->AllocateSingleton<HIDManager>();
		return ptr;
	}

	//------------------------------------------------------------------------------------------------------
	void HIDManager::HandleMessage(Window* window, UINT message, WPARAM wparam, LPARAM lparam)
	{
		
	}

	//------------------------------------------------------------------------------------------------------
	HIDManager::DeviceType HIDManager::ParseMessageType(UINT message)
	{
		DeviceType type;

		if ()
	}
}