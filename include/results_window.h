#ifndef RESULTS_WINDOW_H
#define RESULTS_WINDOW_H
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QList>
#include <QCloseEvent>
#include <QTextEdit>
#include <QLabel>
#include <QMessageBox>
#include <QFrame>

#include <question_utils.h>
#include <utils.h>

using namespace std;


class Result
{
public:
    Result(string question_number,
           bool correct,
           string trials,
           string type,
           string question,
           string real_text_answer = "",
           string given_text_answer = "",
           vector<string> options = vector<string>(),
           string real_multi_answer = "",
           vector<string> given_multi_answers = vector<string>());
    ~Result() {};

    string question_number;
    bool correct;
    string trials;
    string type;
    string question;
    string real_text_answer;
    string given_text_answer;
    vector<string> options;
    string real_multi_answer;
    vector<string> given_multi_answers;
};


class ResultsWindow: public QWidget
{
public:
    ResultsWindow(vector<Result *> *results,
                  QWidget *parent = nullptr);
};



#endif
