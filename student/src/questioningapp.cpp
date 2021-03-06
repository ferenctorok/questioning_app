#include <iostream>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>

#include <questioningapp.h>

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

    // checking the results button:
    buttonResults = set_QPushButton(300, 100, centralwidget, "button_results", "Eredmények",
                                    "Eredmény megtekintése", mainlayout);
    connect(buttonResults, SIGNAL(clicked()), this, SLOT(button_results_clicked()));
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
            // get student name, class and result file name from log, if ther is any:
            string student_name, student_class, student_name_utf8, student_class_utf8, result_file_name;
            getStudentDataFromLog(timestamp, student_name, student_class, result_file_name);

            // if there was no entry yet about this test in the log file, get student name, class
            // and logfile name:
            bool student_data_ok = true;
            if (result_file_name == "NOT_FOUND")
            {
                getStudentData(student_name_utf8, student_class_utf8,
                               student_name, student_class, student_data_ok);
                result_file_name = getResultFileName(utf8String, student_name_utf8, student_class_utf8);
            }

            // if the student data was from any of the sources provided, open the task solving window:
            if (student_data_ok)
            {
                task_solving_window = new TaskSolvingWindow(questions, result_file_name, timestamp,
                                                            student_name, student_class);
                connect(task_solving_window, SIGNAL(IsClosed()), this, SLOT(show_again()));
                hide();
                task_solving_window->show();
            }
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
        string student_name, student_class;
        vector<Result *> *results = readResults(utf8String, student_name, student_class);
        if (results->size() > 0)
        {
            // creating and showing results window:
            results_window = new ResultsWindow(results, student_name, student_class);
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


string QuestioningApp::getResultFileName(string question_file_name,
                                         const string student_name,
                                         const string student_class)
{
    // removing the spaces and points from the name and the class:
    string stud_name_nospace = student_name;
    stud_name_nospace.erase(std::remove(stud_name_nospace.begin(), stud_name_nospace.end(), ' '),
                            stud_name_nospace.end());
    stud_name_nospace.erase(std::remove(stud_name_nospace.begin(), stud_name_nospace.end(), '.'),
                            stud_name_nospace.end());

    string stud_class_nospace = student_class;
    stud_class_nospace.erase(std::remove(stud_class_nospace.begin(), stud_class_nospace.end(), ' '),
                            stud_class_nospace.end());
    stud_class_nospace.erase(std::remove(stud_class_nospace.begin(), stud_class_nospace.end(), '.'),
                            stud_class_nospace.end());


    // creating the file name from this:
    string result_file_name = question_file_name;
    size_t end = result_file_name.rfind(".q");
    result_file_name = result_file_name.substr(0, end);
    result_file_name += ("_" + stud_class_nospace + "_" + stud_name_nospace);
    result_file_name += ".res";
    return result_file_name;
}


void QuestioningApp::getStudentDataFromLog(string timestamp,
                                            string& student_name,
                                            string& student_class,
                                            string& result_file_string)
{
    student_name = "NOT_FOUND";
    student_class = "NOT_FOUND";
    result_file_string = "NOT_FOUND";

    string chapter_marker = "LOG";
    string line;
    streampos oldpos;
    string error_msg;
    string timestamp_candidate;
    string file_name;

    ifstream logfile(LOG_FILE, ios_base::binary);
    if (logfile)
    {
        // search until the first LOG line:
        do
        {
            getline(logfile, line);
        }
        while ((line.find(chapter_marker) == string::npos) && logfile.good());

        while (logfile.good())
        {
            // searching for the timestamp:
            // checking whether there is already a log with this timestamp:
            timestamp_candidate = read_section(logfile, oldpos, "timestamp", chapter_marker, error_msg);

            if (timestamp_candidate == timestamp)
            {
                // reading the data about the student from the file:
                result_file_string = read_section(logfile, oldpos, "result_file", chapter_marker, error_msg);
                student_name = read_section(logfile, oldpos, "student_name", chapter_marker, error_msg);
                student_class = read_section(logfile, oldpos, "student_class", chapter_marker, error_msg);
            }
            else
            {
                // search until next LOG or until the end of the file:
                do
                {
                    getline(logfile, line);
                }
                while ((line.find(chapter_marker) == string::npos) && logfile.good());
            }
        }
    }
}


void QuestioningApp::getStudentData(string& student_name_utf8,
                                    string& student_class_utf8,
                                    string& student_name,
                                    string& student_class,
                                    bool& student_data_ok)
{
    // getting the name of the student:
    QString q_student_name = QInputDialog::getText(this, "Név",
                                           "Kérlek add meg a nevedet", QLineEdit::Normal,
                                           "Vezetéknév Keresztnév", &student_data_ok);
    if (student_data_ok && !q_student_name.isEmpty())
    {
        student_name_utf8 = q_student_name.toLocal8Bit().constData();
        student_name = q_student_name.toStdString();
    }

    else return;

    // getting the class of the student:
    QString q_student_class = QInputDialog::getText(this, "Osztály",
                                           "Kérlek add meg az osztályodat!", QLineEdit::Normal,
                                           "2a", &student_data_ok);
    if (student_data_ok && !q_student_class.isEmpty())
    {
        student_class_utf8 = q_student_class.toLocal8Bit().constData();
        student_class = q_student_class.toStdString();
    }
}


string QuestioningApp::getTimestamp(string filename)
{
    ifstream infile(filename, ios_base::binary);
    streampos oldpos;
    string error_msg = "";
    // reading the timestamp:
    return get_text_after(infile, oldpos, error_msg, "timestamp:");
}







