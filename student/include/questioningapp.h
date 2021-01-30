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
#include <QFont>

#include <question_utils.h>
#include <task_solving.h>
#include <results.h>
#include <utils.h>


class QuestioningApp : public QMainWindow
{
    Q_OBJECT

public:
    QuestioningApp(QWidget *parent = nullptr);
    virtual ~QuestioningApp() {};

protected slots:
    void button_start_clicked();
    void button_results_clicked();
    void show_again();

protected:
    QWidget *centralwidget;
    QHBoxLayout *mainlayout;
    QPushButton *buttonStart;
    QPushButton *buttonResults;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    TaskSolvingWindow *task_solving_window;
    ResultsWindow *results_window;

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
    string getResultFileName(string question_file_name);
    string getTimestamp(string filename);
};
#endif // QUESTIONINGAPP_H
