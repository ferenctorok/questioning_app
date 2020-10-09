#ifndef TASK_SOLVING_h
#define TASK_SOLVING_h
#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QList>
#include <QCloseEvent>
#include <QTextEdit>
#include <QLabel>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

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
    string current_question_type;
    QVBoxLayout *mainlayout;
    QLabel *QuestionLabel;
    QTextEdit *AnswerTextEdit;
    QWidget *MultipleChoiceWidget;
    QVBoxLayout *MultipleChoiceLayout;
    QList<QCheckBox *> answerOptionList;
    QPushButton *NextQuestionButton;

    void closeEvent(QCloseEvent *event);
    void displayNextQuestion();
    void clearOptionList();
    bool isCorrectAnswer();
    string read_text_answer();
};


#endif
