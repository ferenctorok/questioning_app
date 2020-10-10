#ifndef TASK_SOLVING_h
#define TASK_SOLVING_h
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


class TaskSolvingWindow: public QWidget
{
    Q_OBJECT

public:
    TaskSolvingWindow(vector<Question *> *questions,
                      string resultFileName,
                      QWidget *parent = nullptr);
    virtual ~TaskSolvingWindow();

signals:
    void IsClosed();

public slots:
    void next_question_button_clicked();

private:
    string outfileName;
    vector<Question *> *questions;
    int question_counter;
    string current_question_type;
    vector<string> given_text_answers;
    vector<vector<int>> given_multi_answers;

    QVBoxLayout *mainlayout;
    QLabel *InfoLabel;
    QFrame *QuestionFrame;
    QLabel *QuestionLabel;
    QTextEdit *AnswerTextEdit;
    QFrame *MultipleChoiceFrame;
    QVBoxLayout *MultipleChoiceLayout;
    QList<QCheckBox *> answerOptionList;
    QPushButton *NextQuestionButton;

    void closeEvent(QCloseEvent *event);
    void displayNextQuestion();
    void clearOptionList();
    bool isCorrectAnswer();
    string readTextAnswer();
    vector<int> readMultiAnswer();
    void incorrectAnswerDialog();
    void correctAnswerDialog();
    void refreshInfoLabel(Question *question);
    void writeResultToFile(Question *question,
                           bool isCorrect);
};


#endif
