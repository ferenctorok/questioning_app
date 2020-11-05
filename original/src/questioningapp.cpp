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
    this->resize(800, 600);
    this->setWindowTitle("Kérdező app");
    this->setFont(QFont("Times", 14));

    // setting icon:
    setWindowIcon(QIcon(":/question_mark.ico"));

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
                                  "Feladatsor megoldás", mainlayout);
    connect(buttonStart, SIGNAL(clicked()), this, SLOT(button_start_clicked()));

    // new questions button
    buttonNewQuestions = set_QPushButton(300, 100, centralwidget, "buttonNewQuestions", "Új kérdéssor",
                                  "Új kérdéssor összeállítása", mainlayout);
    connect(buttonNewQuestions, SIGNAL(clicked()), this, SLOT(button_new_questions_clicked()));

    // checking the results button:
    buttonResults = set_QPushButton(300, 100, centralwidget, "button_results", "Eredmények",
                                    "Eredmény megtekintése", mainlayout);
    connect(buttonResults, SIGNAL(clicked()), this, SLOT(button_results_clicked()));
}


void QuestioningApp::button_new_questions_clicked()
{
    // file to save into:
    QString fileName = QFileDialog::getSaveFileName(this,
        QString("Kérdéssor mentése ide"), QDir::homePath(), "Question files (*.q)");

    if (!fileName.isEmpty())
    {
        // converting into utf8 string
        string utf8String = fileName.toLocal8Bit().constData();
        // setting up the filename with .q extension if it is missing
        if (!fileName.contains(".q")) fileName.append(".q");
        else if(fileName.lastIndexOf(".q") < (fileName.length() - 3)) fileName.append(".q");

        // setting up new window:
        new_questions_window = new NewQuestionsWindow(utf8String);
        connect(new_questions_window, SIGNAL(IsClosed()), this, SLOT(show_again()));
        hide();
        new_questions_window->show();
    }
}

void QuestioningApp::button_start_clicked()
{
    // question file to open:
    QString fileName = QFileDialog::getOpenFileName(this, "Válassz feladatsort!",
                                                    QDir::homePath(),
                                                    "feladatsor (*.q)");
    if (!fileName.isEmpty())
    {
        // converting into utf8 string
        string utf8String = fileName.toLocal8Bit().constData();
        // reading in the questions from the file.
        vector<Question *> *questions = readQuestions(utf8String);
        // only left here, because then it complains if the timestamp is incorrect.
        string timestamp = getTimestamp(utf8String);
        if (questions->size() > 0)
        {
            // file to save into:
            string result_file_name = getResultFileName(utf8String);
            task_solving_window = new TaskSolvingWindow(questions, result_file_name, timestamp);
            connect(task_solving_window, SIGNAL(IsClosed()), this, SLOT(show_again()));
            hide();
            task_solving_window->show();
        }
        else
        {
            string message = "A kiválasztott fájl nem tartalmaz kérdéseket, vagy hibás.";
            QMessageBox::critical(this, "Hiba!", QString::fromStdString(message));
        }
    }
}


void QuestioningApp::button_results_clicked()
{
    // result file to open:
    QString fileName = QFileDialog::getOpenFileName(this, "Válassz eredmény fájlt!",
                                                    QDir::homePath(),
                                                    "eredmény file (*.res)");
    if (!fileName.isEmpty())
    {
        // converting into utf8 string
        string utf8String = fileName.toLocal8Bit().constData();
        // reading in the results from the file:
        vector<Result *> *results = readResults(utf8String);
        if (results->size() > 0)
        {
            // creating and showing results window:
            results_window = new ResultsWindow(results);
            connect(results_window, SIGNAL(IsClosed()), this, SLOT(show_again()));
            hide();
            results_window->show();
        }
        else
        {
            string message = "A kiválasztott fájl nem tartalmaz eredményeket, vagy hibás.";
            QMessageBox::critical(this, "Hiba!", QString::fromStdString(message));
        }
    }
}


void QuestioningApp::show_again()
{
    show();
}

template<class T>
vector<T *>* QuestioningApp::file_corrupted(const string &error_msg)
{
    string message = "A kiválasztott fájl hibás!\n" + error_msg;
    QMessageBox::critical(this, "Hiba!", QString::fromStdString(message));
    return new vector<T *>;
}
// explicit instantiations:
template
vector<Question *>* QuestioningApp::file_corrupted<Question>(const string &error_msg);
template
vector<Result *>* QuestioningApp::file_corrupted<Result>(const string &error_msg);


string QuestioningApp::get_text_after(ifstream &infile,
                                      streampos &oldpos,
                                      string &error_msg,
                                      const string after_this)
{
    oldpos = infile.tellg();
    string line;
    getline(infile, line);

    // jumping over empty lines
    string whitespaces =  " \t\f\v\n\r";
    while (line.find_first_not_of(whitespaces) == string::npos && !infile.eof())
    {
        getline(infile, line);
    }

    size_t pos = line.find(after_this);
    if (pos != string::npos)
    {
        string return_string = line.substr(pos + after_this.length());
        return_string = return_string.substr(0, return_string.length() - 1);
        return return_string;
    }
    else
    {
        error_msg = "expected keyword: \" " + after_this + " \"\n";
        error_msg += "received line: \" " + line + " \"";
        return "NOT_FOUND";
    }
}


vector<string> QuestioningApp::read_string_list(ifstream &infile,
                                                streampos &oldpos,
                                                string &error_msg)
{
    vector<string> vect;
    string str;
    // reading in the answer options:
    str = get_text_after(infile, oldpos, error_msg, "*");
    if (str == "NOT_FOUND") return vect;
    while (str != "NOT_FOUND")
    {
        vect.push_back(str);
        str = get_text_after(infile, oldpos, error_msg, "*");
    }
    //set back the file to the previous line for further reading:
    infile.seekg(oldpos);
    return vect;
}


string QuestioningApp::getResultFileName(string question_file_name)
{
    string result_file_name = question_file_name;
    size_t end = result_file_name.rfind(".q");
    result_file_name = result_file_name.substr(0, end);
    result_file_name += ".res";
    return result_file_name;
}


string QuestioningApp::getTimestamp(string filename)
{
    ifstream infile(filename, ios_base::binary);
    streampos oldpos;
    string error_msg = "";
    // reading the timestamp:
    return get_text_after(infile, oldpos, error_msg, "timestamp:");
}







