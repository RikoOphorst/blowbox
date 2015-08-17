#include "cvar.h"

#include <iostream>

namespace blowbox
{
	CVar::CVar()
	{

	}

	CVar::~CVar()
	{

	}

	CVar* CVar::Instance()
	{
		static CVar* ptr = new CVar();
		return ptr;
	}

	void CVar::Parse(int argc, char** argv)
	{
		std::map<std::string, std::string> arguments_;

		std::string subject;
		for (int i = 0; i < argc; i++)
		{
			subject = argv[i];

			size_t find = subject.find('=');
			if (find != std::string::npos)
			{
				arguments_.emplace(subject.substr(0, find), subject.substr(find+1, subject.length()));
			}
			else
			{
				arguments_.emplace(subject, subject);
			}
		}

		settings_.boot_folder = argv[0];

		settings_.asset_folder = arguments_.find("-asset_folder") != arguments_.end() ? arguments_.at("-asset_folder") : "";

		if (arguments_.find("-memory") != arguments_.end()) { settings_.memory = stoi(arguments_.at("-memory")); }
	}

	CVar::Settings& CVar::GetSettings()
	{
		return settings_;
	}

	std::map<std::string, std::string>& CVar::GetArguments()
	{
		return arguments_;
	}
}