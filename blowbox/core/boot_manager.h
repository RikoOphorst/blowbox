#pragma once

namespace blowbox
{
	class BootManager
	{
	public:
		BootManager();
		~BootManager();

		void Boot(int argc, char** argv);
	};
}