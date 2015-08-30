#pragma once

#include "../../blowbox/window/window_manager.h"
#include "../../blowbox/memory/memory.h"

#include <vector>

namespace blowbox
{
	const std::vector<UINT> keyboard_messages_ = { WM_KEYDOWN, WM_KEYUP };
	const std::vector<UINT> mouse_messages_ = { WM_LBUTTONDOWN, WM_LBUTTONUP, WM_LBUTTONDBLCLK };
	const std::vector<UINT> gamepad_messages_ = {};
	
	/**
	* @brief Human interface device manager
	* @author Riko Ophorst
	* @class blowbox::HIDManager
	*/
	class HIDManager
	{
	public:
		/**
		* @brief Specifies a type of device
		* @author
		*/
		enum DeviceType
		{
			kKeyboard,
			kMouse,
			kGamePad
		};

		/**
		* @brief Default HIDManager constructor
		*/
		HIDManager();

		/**
		* @brief Default HIDManager destructor
		*/
		~HIDManager();

		/**
		* @brief The singleton instance of the HIDManager
		*/
		static HIDManager* Instance();

		/**
		* @brief Handles a message
		*/
		bool HandleMessage(Window* window, UINT message, WPARAM wparam, LPARAM lparam);
	private:
		/**
		* @brief Depending on the message, chooses a certain device that it comes from
		*/
		DeviceType ParseMessageType(UINT message);
	};
}