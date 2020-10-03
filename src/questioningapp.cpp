#include <iostream>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>

#include <questioningapp.h>
#include <questioningapp.h>
#include <new_questions.h>

QuestioningApp::QuestioningApp(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(600, 400);
    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QStringLiteral("centralwidget"));
    this->setCentralWidget(centralwidget);

    mainlayout = new QHBoxLayout(centralwidget);
    mainlayout->setObjectName(QStringLiteral("mainlayout"));

    buttonStart = new QPushButton(centralwidget);
    buttonStart->setObjectName(QStringLiteral("buttonStart"));
    buttonStart->setText("Kezdés");
    buttonStart->setToolTip("Kérdések kezdése");
    connect(buttonStart, SIGNAL(clicked()), this, SLOT(button_start_clicked()));
    mainlayout->addWidget(buttonStart);

    buttonNewQuestions = new QPushButton(centralwidget);
    buttonNewQuestions->setObjectName(QStringLiteral("buttonNewQuestions"));
    buttonNewQuestions->setText("Új kérdéssor");
    buttonNewQuestions->setToolTip("új kérdéssor összeállítása");
    connect(buttonNewQuestions, SIGNAL(clicked()), this, SLOT(button_new_questions_clicked()));
    mainlayout->addWidget(buttonNewQuestions);

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
    delete buttonNewQuestions;
    delete menubar;
    delete statusbar;
}

void QuestioningApp::button_new_questions_clicked()
{
    /*QString fileName = QFileDialog::getSaveFileName(this,
        QString("Kérdéssor Mentése"));*/
    new_questions_window = new NewQuestionsWindow(this);
    connect(new_questions_window, SIGNAL(IsClosed()), this, SLOT(show_again()));
    this->hide();
    new_questions_window->show();
}

void QuestioningApp::button_start_clicked()
{

}

void QuestioningApp::show_again()
{
    std::cout << "show_again() is called\n";
    this->show();
}

