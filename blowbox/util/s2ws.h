#pragma once

#include <string>
#include <Windows.h>

namespace blowbox
{
	namespace util
	{
		/**
		* @brief Converts a std::string to a std::wstring
		* @param[in] string (const std::string&) the string to be converted
		*/
		std::wstring s2ws(const std::string& string)
		{
			int len;
			int slength = (int)string.length() + 1;
			len = MultiByteToWideChar(CP_ACP, 0, string.c_str(), slength, 0, 0);
			wchar_t* buf = new wchar_t[len];
			MultiByteToWideChar(CP_ACP, 0, string.c_str(), slength, buf, len);
			std::wstring r(buf);
			delete[] buf;
			return r;
		}
	}
}