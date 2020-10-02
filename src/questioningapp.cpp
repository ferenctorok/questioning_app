#include "questioningapp.h"
#include <QMenuBar>
#include <QStatusBar>

QuestioningApp::QuestioningApp(QWidget *parent)
    : QMainWindow(parent)
{
    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QStringLiteral("centralwidget"));
    pushButton = new QPushButton(centralwidget);
    pushButton->setObjectName(QStringLiteral("pushButton"));

    this->setCentralWidget(centralwidget);
    menubar = new QMenuBar(this);
    menubar->setObjectName(QStringLiteral("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 22));
    this->setMenuBar(menubar);
    statusbar = new QStatusBar(this);
    statusbar->setObjectName(QStringLiteral("statusbar"));
    this->setStatusBar(statusbar);

}

QuestioningApp::~QuestioningApp()
{
    delete centralwidget;
    delete pushButton;
    delete menubar;
    delete statusbar;
}

