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
        string next_head_string;
        string type_string;
        string question_string;
        string answer_string;

        getline(infile, head_string);
        // jumping over empty lines:
        while (head_string.find_first_not_of(" ") == string::npos)
        {
            getline(infile, head_string);
        }
        while (!infile.eof()) {
            if (head_string.find("QUESTION") == string::npos) return question_file_corrupted();

            type_string = get_text_after(infile, "type:");
            if (type_string != "text" && type_string != "multi") return question_file_corrupted();

            question_string = get_text_after(infile, "question:");
            if (question_string == "") return question_file_corrupted();

            if (type_string == "text")
            {
                answer_string = get_text_after(infile, "answer:");
                if (answer_string == "") return question_file_corrupted();
            }
            else
            {

            }
            cout << "whole question is done" << endl;
            // jumping over empty lines:
            getline(infile, head_string);
            while (head_string.find_first_not_of(" ") == string::npos && !infile.eof())
            {
                getline(infile, head_string);
            }
        }
    }


    return new vector<Question *>;
}


vector<Question *>* QuestioningApp::question_file_corrupted()
{
    QMessageBox::critical(this, "Hiba!", "A kiválasztott fájl hibás!");
    return new vector<Question *>;
}


string QuestioningApp::get_text_after(ifstream &infile,
                                      const string after_this)
{
    string line;
    getline(infile, line);

    // jumping over empty lines
    while (line.find_first_not_of(" ") == string::npos && !infile.eof())
    {
        getline(infile, line);
    }

    size_t pos = line.find(after_this);
    cout << line << endl;
    if (pos != string::npos) return line.substr(pos + after_this.length());
    else return "";
}










