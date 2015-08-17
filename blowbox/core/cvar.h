#pragma once

#include <string>
#include <map>

namespace blowbox
{
	class CVar
	{
	public:
		struct Settings
		{
			std::string boot_folder;
			std::string asset_folder;
			unsigned int memory = 500000000;
		};

		CVar();
		~CVar();

		static CVar* Instance();

		void Parse(int argc, char** argv);

		Settings& GetSettings();

		std::map<std::string, std::string>& GetArguments();
	private:
		Settings settings_; //<! Keeps a hold of the given cvars
		std::map<std::string, std::string> arguments_; //<! Keeps a hold of the unparsed cvars
	};
}