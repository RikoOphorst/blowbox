#include "console\console.h"
#include "network\server.h"
#include <time.h>

#include <fstream>

using namespace console;
using namespace network;

#include <iostream>

int main(int argc, char** argv)
{
	QApplication QApp(argc, argv);

	Console* console = new Console();

	Server* server = new Server();
	server->Initialise(console);

	server->Run();

	time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t);

	QString year = QString::number(now.tm_year + 1900);

	QString month = QString::number(now.tm_mon + 1);
	if (month.size() < 2)
		month = "0" + month;

	QString day = QString::number(now.tm_mday);
	if (day.size() < 2)
		day = "0" + day;

	QString hour = QString::number(now.tm_hour);
	if (hour.size() < 2)
		hour = "0" + hour;

	QString min = QString::number(now.tm_min);
	if (min.size() < 2)
		min = "0" + min;

	QString sec = QString::number(now.tm_sec);
	if (sec.size() < 2)
		sec = "0" + sec;

	QString timeStamp = year + month + day + "@" + hour + min + sec;

	std::ofstream plainLogFile;
	plainLogFile.open(std::string("log") + timeStamp.toUtf8().constData() + ".txt");
	plainLogFile << console->GetQtConsole()->logging_view->toPlainText().toUtf8().constData();
	plainLogFile.close();

	std::ofstream htmlLogFile;
	htmlLogFile.open(std::string("log") + timeStamp.toUtf8().constData() + ".html");
	htmlLogFile << console->GetQtConsole()->logging_view->toHtml().toUtf8().constData();
	htmlLogFile.close();

	return 0;
}