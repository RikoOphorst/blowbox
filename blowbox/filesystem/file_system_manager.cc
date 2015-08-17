#include "file_system_manager.h"

#include <iostream>
#include <fstream>

namespace blowbox
{
	FileSystemManager::FileSystemManager()
	{
		
	}

	FileSystemManager::~FileSystemManager()
	{

	}

	FileSystemManager* FileSystemManager::Instance()
	{
		static FileSystemManager* ptr = Memory::Instance()->AllocateSingleton<FileSystemManager>();
		return ptr;
	}

	void FileSystemManager::StartUp()
	{
		
	}

	void FileSystemManager::ShutDown()
	{

	}

	void FileSystemManager::ReadFile(const std::string& path, std::string& out)
	{
		std::fstream stream;
		stream.open(path, std::ios::in);

		if (stream.is_open())
		{
			std::string line;
			while (std::getline(stream, line))
			{
				out += line + '\n';
			}

			stream.close();
		}
	}

	void FileSystemManager::WriteFile(const std::string& path, std::string& text)
	{
		std::fstream stream;
		stream.open(path, std::ios::out);

		stream.write(text.c_str(), text.size());

		stream.close();
	}
}