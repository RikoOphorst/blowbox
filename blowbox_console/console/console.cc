#include "console.h"

#include <iostream>
#include <time.h>

namespace console
{

	//------------------------------------------------------------------------------------------------------
	Console::Console()
	{
		main_window_ = new QMainWindow();
		qt_console_ = new Ui::Console();
		qt_console_->setupUi(main_window_);

		QPalette palette;
		palette.setColor(QPalette::Window, QColor(8, 38, 36));
		palette.setColor(QPalette::WindowText, QColor(166, 207, 207));
		palette.setColor(QPalette::Base, QColor(23, 24, 26));
		palette.setColor(QPalette::AlternateBase, QColor(23, 24, 26));
		palette.setColor(QPalette::ToolTipBase, Qt::white);
		palette.setColor(QPalette::ToolTipText, Qt::white);
		palette.setColor(QPalette::Text, QColor(166, 207, 207));
		palette.setColor(QPalette::Button, QColor(23, 24, 26));
		palette.setColor(QPalette::ButtonText, Qt::white);
		palette.setColor(QPalette::BrightText, Qt::red);
		palette.setColor(QPalette::Link, QColor(159, 164, 98));

		palette.setColor(QPalette::Highlight, QColor(100, 106, 120));
		palette.setColor(QPalette::HighlightedText, Qt::black);

		qt_console_->tab_widget->setStyleSheet(QString::fromUtf8(""
			"QTabWidget::pane {"
			"	border: 2px solid rgb(5, 10, 5);"
			"	background-color: rgb(23, 24, 26);"
			"}"
			"QTabBar::tab {"
			"	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 rgb(45, 45, 30), stop: 1.0 rgb(15, 15, 15));"
			"	color: rgb(160, 160, 160);"
			"}"
			"QTabBar::tab::hover {"
			"	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 rgb(55, 55, 40), stop: 1.0 rgb(25, 25, 25));"
			"	color: rgb(180, 180, 180);"
			"}"
			"QTabBar::tab::selected {"
			"	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 rgb(50, 50, 35), stop: 1.0 rgb(20, 20, 20));"
			"	color: rgb(200, 200, 200);"
			"}"
			));

		qt_console_->logging_view->setStyleSheet(""
			"QTextEdit, QTextEdit::focus {"
			"	background-color: rgb(25, 25, 35);"
			//"	background-image: url('D:/header.png');"
			"	border: 1px solid rgb(100, 100, 100);"
			"	color: rgb(150, 150, 150);"
			"	font-family: Consolas;"
			"}"
			);

		qt_console_->logging_view->setReadOnly(true);

		qt_console_->input_box->setStyleSheet(""
			"QPlainTextEdit {"
			"	background-color: rgb(25, 25, 35);"
			"	border: 1px solid rgb(100, 100, 100);"
			"	color: rgb(150, 150, 150);"
			"	font-family: Consolas;"
			"}"
			"QPlainTextEdit::hover, QPlainTextEdit::focus {"
			"	background-color: rgb(35, 35, 45);"
			"	border: 1px solid rgb(100, 100, 100);"
			"}"
			);

		main_window_->activateWindow();
		main_window_->show();

		main_window_->setPalette(palette);

		main_window_->move(1920.0f + (1920.0f / 2.0f) - main_window_->size().width() / 2.0f, (1080 / 2.0f) - main_window_->size().height() / 2.0f);
	}

	//------------------------------------------------------------------------------------------------------
	Console::~Console()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void Console::AddLog(const network::ConsoleMessageTextLog& log)
	{
		time_t t = time(0);
		struct tm now;
		localtime_s(&now, &t);
		QString hour = QString::number(now.tm_hour);

		if (hour.size() < 2)
		{
			hour = "0" + hour;
		}

		QString min = QString::number(now.tm_min);
		if (min.size() < 2)
			min = "0" + min;

		QString sec = QString::number(now.tm_sec);
		if (sec.size() < 2)
			sec = "0" + sec;

		QString timeStamp = hour + ":" + min + ":" + sec + " ";


		std::string string = std::string(log.log, log.log_length);

		QTextCursor cursor = qt_console_->logging_view->textCursor();
		cursor.movePosition(QTextCursor::End);

		string += "\n";

		QTextCharFormat format;
		format.setForeground(QBrush(QColor(log.foregroundR, log.foregroundG, log.foregroundB, log.foregroundA)));
		format.setBackground(QBrush(QColor(log.backgroundR, log.backgroundG, log.backgroundB, log.backgroundA)));
		format.setFontPointSize(10);
		cursor.setCharFormat(format);

		cursor.insertText(timeStamp + string.c_str());
		cursor.movePosition(QTextCursor::End);

		qt_console_->logging_view->setTextCursor(cursor);
	}

	//------------------------------------------------------------------------------------------------------
	void Console::AddLog(const std::string& log)
	{
		network::ConsoleMessageTextLog msg;

		memcpy(msg.log, log.c_str(), log.size());
		msg.log_length = log.size();
		msg.foregroundR = 150;
		msg.foregroundG = 150;
		msg.foregroundB = 150;
		msg.foregroundA = 255;
		msg.backgroundR = 0;
		msg.backgroundG = 0;
		msg.backgroundB = 0;
		msg.backgroundA = 0;
		msg.dateSend = time(0);

		AddLog(msg);
	}

	//------------------------------------------------------------------------------------------------------
	QMainWindow* Console::GetQtMainWindow()
	{
		return main_window_;
	}

	//------------------------------------------------------------------------------------------------------
	Ui::Console* Console::GetQtConsole()
	{
		return qt_console_;
	}

	//------------------------------------------------------------------------------------------------------
	bool Console::IsClosed()
	{
		return !main_window_->isVisible();
	}
}