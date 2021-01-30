#ifndef TASK_SOLVING_H
#define TASK_SOLVING_H
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
#include <QFont>

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
    void correction_button_clicked();
    void previous_button_clicked();
    void next_button_clicked();

private:
    vector<Question *> *questions;
    int question_counter;
    string current_question_type;
    vector<string> given_text_answers;
    vector<vector<int>> given_multi_answers;

    QVBoxLayout *mainlayout;
    QLabel *InfoLabel;
    QLabel *QuestionLabel;
    QTextEdit *AnswerTextEdit;
    QFrame *MultipleChoiceFrame;
    QVBoxLayout *MultipleChoiceLayout;
    QList<QCheckBox *> answerOptionList;
    QHBoxLayout *ButtonLayout;
    QPushButton *CorrectionButton;
    QPushButton *PreviousButton;
    QPushButton *NextButton;

    void closeEvent(QCloseEvent *event);
    void displayQuestion();
    void clearOptionList();
    bool isCorrectAnswer();
    string readTextAnswer();
    vector<int> readMultiAnswer();
    void incorrectAnswerDialog();
    void correctAnswerDialog();
    void refreshInfoLabel(Question *question);
    void writeResultToFile(Question *question,
                           bool isCorrect);
    string givenAnswersToSring();
    string getTextAfter(ifstream &infile,
                        string after_this);
};


#endif
