/********************************************************************************
** Form generated from reading UI file 'console_design.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CONSOLE_DESIGN_H
#define CONSOLE_DESIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Console
{
public:
    QWidget *centralwidget;
    QTabWidget *tab_widget;
    QWidget *tab_logging;
    QTextEdit *logging_view;
    QPlainTextEdit *input_box;
    QWidget *tab_settings;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *layout;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;

    void setupUi(QMainWindow *Console)
    {
        if (Console->objectName().isEmpty())
            Console->setObjectName(QStringLiteral("Console"));
        Console->setEnabled(true);
        Console->resize(800, 595);
        centralwidget = new QWidget(Console);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tab_widget = new QTabWidget(centralwidget);
        tab_widget->setObjectName(QStringLiteral("tab_widget"));
        tab_widget->setEnabled(true);
        tab_widget->setGeometry(QRect(6, 9, 791, 581));
        tab_logging = new QWidget();
        tab_logging->setObjectName(QStringLiteral("tab_logging"));
        logging_view = new QTextEdit(tab_logging);
        logging_view->setObjectName(QStringLiteral("logging_view"));
        logging_view->setGeometry(QRect(10, 10, 761, 491));
        input_box = new QPlainTextEdit(tab_logging);
        input_box->setObjectName(QStringLiteral("input_box"));
        input_box->setGeometry(QRect(10, 510, 761, 41));
        tab_widget->addTab(tab_logging, QString());
        tab_settings = new QWidget();
        tab_settings->setObjectName(QStringLiteral("tab_settings"));
        verticalLayoutWidget = new QWidget(tab_settings);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 171, 101));
        layout = new QVBoxLayout(verticalLayoutWidget);
        layout->setObjectName(QStringLiteral("layout"));
        layout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        layout->addWidget(label_3);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        layout->addWidget(label_2);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        layout->addWidget(label);

        tab_widget->addTab(tab_settings, QString());
        Console->setCentralWidget(centralwidget);

        retranslateUi(Console);

        tab_widget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Console);
    } // setupUi

    void retranslateUi(QMainWindow *Console)
    {
        Console->setWindowTitle(QApplication::translate("Console", "Blowbox Console", 0));
        logging_view->setHtml(QApplication::translate("Console", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        tab_widget->setTabText(tab_widget->indexOf(tab_logging), QApplication::translate("Console", "Logging", 0));
        label_3->setText(QApplication::translate("Console", "Number of objects", 0));
        label_2->setText(QApplication::translate("Console", "Frame rate", 0));
        label->setText(QApplication::translate("Console", "Draw calls", 0));
        tab_widget->setTabText(tab_widget->indexOf(tab_settings), QApplication::translate("Console", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class Console: public Ui_Console {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CONSOLE_DESIGN_H
