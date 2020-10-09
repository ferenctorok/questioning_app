#ifndef TASK_SOLVING_h
#define TASK_SOLVING_h
#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QList>
#include <QCloseEvent>
#include <QTextEdit>
#include <QLabel>
#include <vector>
#include <iostream>
#include <fstream>

#include <question_utils.h>
#include <utils.h>

using namespace std;


class TaskSolvingWindow: public QWidget
{
    Q_OBJECT

public:
    TaskSolvingWindow(vector<Question *> *questions,
                      QWidget *parent = nullptr);
    virtual ~TaskSolvingWindow();

signals:
    void IsClosed();

public slots:
    void next_question_button_clicked();

private:
    vector<Question *> *questions;
    int question_counter;
    QVBoxLayout *mainlayout;
    QLabel *QuestionLabel;
    QTextEdit *AnswerTextEdit;
    QWidget *MultipleChoiceWidget;
    QVBoxLayout *MultipleChoiceLayout;
    QList<QRadioButton *> answerOptionList;
    QPushButton *NextQuestionButton;

    void closeEvent(QCloseEvent *event);
    void displayNextQuestion();
};


#endif
