#ifndef QUESTIONINGAPP_H
#define QUESTIONINGAPP_H
#include <iostream>

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStatusBar>
#include <QMenuBar>
#include <QMessageBox>

#include <question_utils.h>
#include <new_questions.h>
#include <task_solving.h>
#include <results_window.h>


class QuestioningApp : public QMainWindow
{
    Q_OBJECT

public:
    QuestioningApp(QWidget *parent = nullptr);
    virtual ~QuestioningApp() {};

protected slots:
    void button_new_questions_clicked();
    void button_start_clicked();
    void show_again();

protected:
    QWidget *centralwidget;
    QHBoxLayout *mainlayout;
    QPushButton *buttonNewQuestions;
    QPushButton *buttonStart;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    NewQuestionsWindow *new_questions_window;
    TaskSolvingWindow *task_solving_window;

    vector<Question *>* readQuestions(string filename);
    vector<Result *>* readResults(string filename);
    template<class T> vector<T *>* file_corrupted(const string &error_msg = "");
    string get_text_after(ifstream &infile,
                          streampos &oldpos,
                          string &error_msg,
                          const string after_this = "");
    vector<string> read_string_list(ifstream &infile,
                                    streampos &oldpos,
                                    string &error_msg);
    vector<int> get_multi_answers_from_string(string str);
    string getResultFileName(string question_file_name);
    string getTimestamp(string filename);
};
#endif // QUESTIONINGAPP_H
