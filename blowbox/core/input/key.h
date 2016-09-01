#pragma once

#include <string>

#ifndef KEY_HEADER
#define KEY_HEADER

namespace blowbox
{
	/**
	* @enum blowbox::BB_KEY_TYPE
	* @author Riko Ophorst
	* @brief Enumerates all keys on the keyboard (and then some)
	*/
	enum BB_KEY_TYPE
	{
		BB_KEY_BACKSPACE = 0x08,
		BB_KEY_TAB = 0x09,
		BB_KEY_CLEAR = 0x0C,
		BB_KEY_ENTER = 0x0D,
		BB_KEY_SHIFT = 0x10,
		BB_KEY_CONTROL = 0x11,
		BB_KEY_ALT = 0x12,
		BB_KEY_PAUSE = 0x13,
		BB_KEY_CAPS_LOCK = 0x14,
		BB_KEY_ESCAPE = 0x1B,
		BB_KEY_SPACE = 0x20,
		BB_KEY_PAGE_UP = 0x21,
		BB_KEY_PAGE_DOWN = 0x22,
		BB_KEY_END = 0x23,
		BB_KEY_HOME = 0x24,
		BB_KEY_LEFT = 0x25,
		BB_KEY_UP = 0x26,
		BB_KEY_RIGHT = 0x27,
		BB_KEY_DOWN = 0x28,
		BB_KEY_SELECT = 0x29,
		BB_KEY_PRINT = 0x2A,
		BB_KEY_EXECUTE = 0x2B,
		BB_KEY_PRINT_SCREEN = 0x2C,
		BB_KEY_INSERT = 0x2D,
		BB_KEY_DELETE = 0x2E,
		BB_KEY_HELP = 0x2F,
		BB_KEY_ZERO = 0x30,
		BB_KEY_ONE = 0x31,
		BB_KEY_TWO = 0x32,
		BB_KEY_THREE = 0x33,
		BB_KEY_FOUR = 0x34,
		BB_KEY_FIVE = 0x35,
		BB_KEY_SIX = 0x36,
		BB_KEY_SEVEN = 0x37,
		BB_KEY_EIGHT = 0x38,
		BB_KEY_NINE = 0x39,
		BB_KEY_A = 0x41,
		BB_KEY_B = 0x42,
		BB_KEY_C = 0x43,
		BB_KEY_D = 0x44,
		BB_KEY_E = 0x45,
		BB_KEY_F = 0x46,
		BB_KEY_G = 0x47,
		BB_KEY_H = 0x48,
		BB_KEY_I = 0x49,
		BB_KEY_J = 0x4A,
		BB_KEY_K = 0x4B,
		BB_KEY_L = 0x4C,
		BB_KEY_M = 0x4D,
		BB_KEY_N = 0x4E,
		BB_KEY_O = 0x4F,
		BB_KEY_P = 0x50,
		BB_KEY_Q = 0x51,
		BB_KEY_R = 0x52,
		BB_KEY_S = 0x53,
		BB_KEY_T = 0x54,
		BB_KEY_U = 0x55,
		BB_KEY_V = 0x56,
		BB_KEY_W = 0x57,
		BB_KEY_X = 0x58,
		BB_KEY_Y = 0x59,
		BB_KEY_Z = 0x5A,
		BB_KEY_LEFT_WINDOWS_KEY = 0x5B,
		BB_KEY_RIGHT_WINDOWS_KEY = 0x5C,
		BB_KEY_APPLICATIONS_KEY = 0x5D,
		BB_KEY_SLEEP = 0x5F,
		BB_KEY_NUMPAD0 = 0x60,
		BB_KEY_NUMPAD1 = 0x61,
		BB_KEY_NUMPAD2 = 0x62,
		BB_KEY_NUMPAD3 = 0x63,
		BB_KEY_NUMPAD4 = 0x64,
		BB_KEY_NUMPAD5 = 0x65,
		BB_KEY_NUMPAD6 = 0x66,
		BB_KEY_NUMPAD7 = 0x67,
		BB_KEY_NUMPAD8 = 0x68,
		BB_KEY_NUMPAD9 = 0x69,
		BB_KEY_MULTIPLY = 0x6A,
		BB_KEY_PLUS = 0x6B,
		BB_KEY_SEPERATOR = 0x6C,
		BB_KEY_MINUS = 0x6D,
		BB_KEY_DECIMAL = 0x6E,
		BB_KEY_DIVIDE = 0x6F,
		BB_KEY_F1 = 0x70,
		BB_KEY_F2 = 0x71,
		BB_KEY_F3 = 0x72,
		BB_KEY_F4 = 0x73,
		BB_KEY_F5 = 0x74,
		BB_KEY_F6 = 0x75,
		BB_KEY_F7 = 0x76,
		BB_KEY_F8 = 0x77,
		BB_KEY_F9 = 0x78,
		BB_KEY_F10 = 0x79,
		BB_KEY_F11 = 0x7A,
		BB_KEY_F12 = 0x7B,

		BB_KEY_F13 = 0x7C,
		BB_KEY_F14 = 0x7D,
		BB_KEY_F15 = 0x7E,
		BB_KEY_F16 = 0x7F,
		BB_KEY_F17 = 0x80,
		BB_KEY_F18 = 0x81,
		BB_KEY_F19 = 0x82,
		BB_KEY_F20 = 0x83,
		BB_KEY_F21 = 0x84,
		BB_KEY_F22 = 0x85,
		BB_KEY_F23 = 0x86,
		BB_KEY_F24 = 0x87,

		BB_KEY_NUM_LOCK = 0x90,
		BB_KEY_SCROLL_LOCK = 0x91,
		BB_KEY_LEFT_SHIFT = 0xA0,
		BB_KEY_RIGHT_SHIFT = 0xA1,
		BB_KEY_LEFT_CONTROL = 0xA2,
		BB_KEY_RIGHT_CONTROL = 0xA3,
		BB_KEY_LEFT_MENU = 0xA4,
		BB_KEY_RIGHT_MENU = 0xA5,
		BB_KEY_BROWSER_BACK = 0xA6,
		BB_KEY_BROWSER_FORWARD = 0xA7,
		BB_KEY_BROWSER_REFRESH = 0xA8,
		BB_KEY_BROWSER_STOP = 0xA9,
		BB_KEY_BROWSER_SEARCH = 0xAA,
		BB_KEY_BROWSER_FAVORITES = 0xAB,
		BB_KEY_BROWSER_HOME = 0xAC,
		BB_KEY_VOLUME_MUTE = 0xAD,
		BB_KEY_VOLUME_DOWN = 0xAE,
		BB_KEY_VOLUME_UP = 0xAF,
		BB_KEY_NEXT_TRACK = 0xB0,
		BB_KEY_PREVIOUS_TRACK = 0xB1,
		BB_KEY_STOP_MEDIA = 0xB2,
		BB_KEY_PLAY_PAUSE = 0xB3,
		BB_KEY_LAUNCH_MAIL = 0xB4,
		BB_KEY_SELECT_MEDIA = 0xB5,
		BB_KEY_LAUNCH_APP1 = 0xB6,
		BB_KEY_LAUNCH_APP2 = 0xB7,
		BB_KEY_OEM1 = 0xBA,
		BB_KEY_OEMPLUS = 0xB8,
		BB_KEY_OEMCOMMA = 0xBC,
		BB_KEY_OEMMINUS = 0xBD,
		BB_KEY_OEMPERIOD = 0xBE,
		BB_KEY_OEM2 = 0xBF,
		BB_KEY_OEM3 = 0xC0,
		BB_KEY_OEM4 = 0xDB,
		BB_KEY_OEM5 = 0xDC,
		BB_KEY_OEM6 = 0xDD,
		BB_KEY_OEM7 = 0xDE,
		BB_KEY_OEM8 = 0xDF,
		BB_KEY_OEM102 = 0xE2,

		BB_KEY_PROCESS = 0xE5,
		BB_KEY_PACKET = 0xE7,
		BB_KEY_ATTN = 0xF6,
		BB_KEY_CRSEL = 0xF7,
		BB_KEY_EXSEL = 0xF8,
		BB_KEY_ERASEEOF = 0xF9,
		BB_KEY_PLAY = 0xFA,
		BB_KEY_ZOOM = 0xFB,
		BB_KEY_PA1 = 0xFD,
		BB_KEY_OEMCLEAR = 0xFE,

		BB_KEY_NULL = 0
	};

	/**
	* @struct blowbox::KeyState
	* @author Riko Ophorst
	* @brief The state of a key
	*/
	struct KeyState
	{
		/**
		* @brief KeyState constructor
		*/
		KeyState() : key(BB_KEY_NULL), is_pressed(false), is_released(false), is_down(false) {};
		BB_KEY_TYPE key; //<! The key this KeyState represents
		bool is_pressed; //<! If a key is down, this will be true for one frame and then return to false, even if the key is continued to be held down after the first registered press-frame
		bool is_released; //<! If a key returns to the up-state, this will be true for one frame and then return to false
		bool is_down; //<! Is the key down?
	};

	/**
	* @brief Converts a key to a name-string
	* @param[in]	key		The key to be converted
	*/
	std::string KeyToString(const BB_KEY_TYPE& key);
	
	/**
	* @brief Converts a given key to a char
	* @param[in]	key			The key to be converted
	* @param[in]	shift		Is shift being held?
	* @param[in]	caps_lock	Is caps lock on?
	*/
	char KeyToChar(const BB_KEY_TYPE& key, bool shift = false, bool caps_lock = false);

	/**
	* @brief Is the given key a typeable character?
	* @param[in]	key		The key to be checked
	*/
	bool IsKeyAChar(const BB_KEY_TYPE& key);

	/**
	* @brief Converts a name to a BB_KEY_TYPE
	* @param[in]	name	the name of the key you want the BB_KEY_* of
	*/
	BB_KEY_TYPE StringToKey(const char* name);

	/**
	* @brief Converts a given char to uppercase
	* @param[in]	c	the char to convert
	*/
	char ToUpper(char c);
	
	/**
	* @brief Converts a given char to lowercase
	* @param[in]	c	the char to convert
	*/
	char ToLower(char c);
}

#endif