#pragma once

#include "../design/console_design.h"
#include "../network/message_types.h"

#include <string>

namespace console
{
	class Console
	{
	public:
		Console();
		~Console();

		void AddLog(const std::string& log);
		void AddLog(const network::ConsoleMessageTextLog& log);

		QMainWindow* GetQtMainWindow();
		Ui::Console* GetQtConsole();

		bool IsClosed();
	private:
		QMainWindow* main_window_;
		Ui::Console* qt_console_;
	};
}