#ifndef RESULTS_WINDOW_H
#define RESULTS_WINDOW_H
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <QWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QList>
#include <QCloseEvent>
#include <QLabel>
#include <QFrame>
#include <QScrollArea>

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
           string real_answer = "",
           vector<string> options = vector<string>(),
           vector<string> given_answers = vector<string>());
    ~Result() {};

    string question_number;
    bool correct;
    string trials;
    string type;
    string question;
    string real_answer;
    vector<string> options;
    vector<string> given_answers;
};


class ResultsWindow: public QWidget
{
    Q_OBJECT

public:
    ResultsWindow(vector<Result *> *results,
                  QWidget *parent = nullptr);
    virtual ~ResultsWindow();

signals:
    void IsClosed();

private:
    vector<Result *> *results;

    QHBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QWidget *ScrollAreaWidget;
    QVBoxLayout *ScrollAreaWidgetLayout;
    QList<QPushButton *> *buttonList;
    QList<QLabel *> *labelList;

    void closeEvent(QCloseEvent *event);
    void print_which_button();
};



#endif









