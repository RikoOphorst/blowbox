#pragma once

#include "../../blowbox/memory/memory.h"
#include <string>

namespace blowbox
{
	class FileSystemManager
	{
	public:
		FileSystemManager();
		~FileSystemManager();

		static FileSystemManager* Instance();

		void StartUp();
		void ShutDown();

		void ReadFile(const std::string& path, std::string& out);
		void WriteFile(const std::string& path, std::string& text);
	};
}