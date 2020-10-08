#include <iostream>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>

#include <questioningapp.h>
#include <utils.h>
#include <new_questions.h>

QuestioningApp::QuestioningApp(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(600, 400);
    this->setWindowTitle("Kérdező app");
    // central widget
    centralwidget = set_centralwidget(this, "centralwidget");

    // main layout
    mainlayout = set_QHBoxLayout(centralwidget, "mainlayout");
    //mainlayout->setAlignment(Qt::AlignCenter);

    // menu bar
    menubar = set_QMenuBar(this, "menubar");
    this->setMenuBar(menubar);

    // status bar
    statusbar = set_QStatusBar(this, "statusbar");
    this->setStatusBar(statusbar);

    // start button
    buttonStart = set_QPushButton(300, 100, centralwidget, "buttonStart", "Kezdés",
                                  "Kérdések kezdése", mainlayout);
    connect(buttonStart, SIGNAL(clicked()), this, SLOT(button_start_clicked()));

    // new questions button
    buttonNewQuestions = set_QPushButton(300, 100, centralwidget, "buttonNewQuestions", "Új kérdéssor",
                                  "Új kérdéssor összeállítása", mainlayout);
    connect(buttonNewQuestions, SIGNAL(clicked()), this, SLOT(button_new_questions_clicked()));
}


void QuestioningApp::button_new_questions_clicked()
{
    // file name to save:
    QString fileName = QFileDialog::getSaveFileName(this,
        QString("Kérdéssor Mentése"));

    // setting up new window:
    new_questions_window = new NewQuestionsWindow(fileName);
    connect(new_questions_window, SIGNAL(IsClosed()), this, SLOT(show_again()));
    hide();
    new_questions_window->show();
}

void QuestioningApp::button_start_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Kérdéssor választása",
                                                    "",
                                                    tr("Question files (*.txt)"));
    if (!fileName.isEmpty())
    {
        vector<Question *> *questions = readQuestions(fileName.toStdString());
    }
}


void QuestioningApp::show_again()
{
    show();
}


vector<Question *>* QuestioningApp::readQuestions(string filename)
{
    ifstream infile(filename);
    if (infile.is_open())
    {
        string head_string;
        string type_string;
        //while (!infile.eof()) {
            getline(infile, head_string);
            if (head_string.find("QUESTION") == string::npos) return question_file_corrupted();

            type_string = read_type(infile);
            if (type_string != "text" && type_string != "multi") return question_file_corrupted();


        //}
    }


    return new vector<Question *>;
}


vector<Question *>* QuestioningApp::question_file_corrupted()
{
    QMessageBox::critical(this, "Hiba!", "A kiválasztott fájl hibás!");
    return new vector<Question *>;
}


string QuestioningApp::read_type(ifstream &infile)
{
    string line;
    getline(infile, line);
    size_t pos = line.find("type:");
    if (pos != string::npos) return line.substr(pos + 5);
    else return "";
}










