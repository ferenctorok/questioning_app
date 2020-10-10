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
        task_solving_window = new TaskSolvingWindow(questions);
        connect(task_solving_window, SIGNAL(IsClosed()), this, SLOT(show_again()));
        hide();
        task_solving_window->show();
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
        string error_msg = "";
        streampos oldpos;
        string question_num_string;
        int question_num;
        string next_head_string;
        string type_string;
        string num_of_trials_string;
        int num_of_trials;
        string question_string;
        string answer_string;
        string head_answer_option_string;
        string answer_option_string;
        vector<string> answer_options_vect;
        vector<int> multi_answers_vect;
        vector<Question *> *questions_vect = new vector<Question *>;

        while (!infile.eof()) {
            // empty vectors:
            answer_options_vect.clear();
            multi_answers_vect.clear();

            //jump back to last read line if there is still left from the file:
            infile.seekg(oldpos);
            question_num_string = get_text_after(infile, oldpos, error_msg, "QUESTION");
            if (question_num_string == "NOT_FOUND") return question_file_corrupted(error_msg);
            question_num = stoi(question_num_string);

            // reading the number of trials:
            num_of_trials_string = get_text_after(infile, oldpos, error_msg, "trials:");
            if (num_of_trials_string == "NOT_FOUND") return question_file_corrupted(error_msg);
            num_of_trials = stoi(num_of_trials_string);

            // reading the type of the question:
            type_string = get_text_after(infile, oldpos, error_msg, "type:");
            if (type_string != "text" && type_string != "multi") return question_file_corrupted(error_msg);

            // reading the question:
            question_string = get_text_after(infile, oldpos, error_msg, "question:");
            if (question_string == "NOT_FOUND") return question_file_corrupted(error_msg);

            if (type_string == "text")
            {
                // reading the answer:
                answer_string = get_text_after(infile, oldpos, error_msg, "answer:");
                if (answer_string == "NOT_FOUND") return question_file_corrupted(error_msg);

                // adding the new question to the vector:
                questions_vect->push_back(new TextQuestion(question_string, type_string,
                                                           question_num, num_of_trials, answer_string));
            }
            else
            {
                // check whether there is the header answer_options:
                head_answer_option_string = get_text_after(infile, oldpos, error_msg, "answer_options:");
                if (head_answer_option_string == "NOT_FOUND") return question_file_corrupted(error_msg);

                // reading in the answer options:
                answer_option_string = get_text_after(infile, oldpos, error_msg, "*");
                if (answer_option_string == "NOT_FOUND") return question_file_corrupted(error_msg);
                while (answer_option_string != "NOT_FOUND")
                {
                    answer_options_vect.push_back(answer_option_string);
                    answer_option_string = get_text_after(infile, oldpos, error_msg, "*");
                }
                //set back the file to the previous line for further reading:
                infile.seekg(oldpos);

                // reading the answers:
                answer_string = get_text_after(infile, oldpos, error_msg, "answers:");
                if (answer_string == "NOT_FOUND") return question_file_corrupted(error_msg);
                multi_answers_vect = get_multi_answers_from_string(answer_string);

                // adding the new question to the vector:
                questions_vect->push_back(new MultiChoiceQuestion(question_string, type_string, question_num,
                                                                  num_of_trials, answer_options_vect, multi_answers_vect));
            }
            // jumping over empty lines:
            getline(infile, question_num_string);
            oldpos = infile.tellg();
            while (question_num_string.find_first_not_of(" ") == string::npos && !infile.eof())
            {
                getline(infile, question_num_string);
            }
        }
        return questions_vect;
    }
    else return new vector<Question *>;
}


vector<Question *>* QuestioningApp::question_file_corrupted(const string &error_msg)
{
    string message = "A kiválasztott fájl hibás!\n" + error_msg;
    QMessageBox::critical(this, "Hiba!", QString::fromStdString(message));
    return new vector<Question *>;
}


string QuestioningApp::get_text_after(ifstream &infile,
                                      streampos &oldpos,
                                      string &error_msg,
                                      const string after_this)
{
    oldpos = infile.tellg();
    string line;
    getline(infile, line);

    // jumping over empty lines
    while (line.find_first_not_of(" ") == string::npos && !infile.eof())
    {
        getline(infile, line);
    }

    size_t pos = line.find(after_this);
    if (pos != string::npos) return line.substr(pos + after_this.length());
    else
    {
        error_msg = "expected keyword: \" " + after_this + " \"\n";
        error_msg += "received line: \" " + line + " \"";
        return "NOT_FOUND";
    }
}


vector<int> QuestioningApp::get_multi_answers_from_string(string str)
{
    vector<int> answers;
    size_t pos_end = str.find(",");
    size_t pos_beg(0);
    string actual_string;
    while (pos_end != string::npos)
    {
        actual_string = str.substr(pos_beg, pos_end - pos_beg);
        answers.push_back(std::stoi(actual_string));
        pos_beg = pos_end + 1;
        pos_end = str.find(",", pos_beg);
    }
    return answers;
}







