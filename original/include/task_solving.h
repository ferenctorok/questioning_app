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

#include <question_utils.h>
#include <utils.h>

using namespace std;


extern const string LOG_FILE;

class TaskSolvingWindow: public QWidget
{
    Q_OBJECT

public:
    TaskSolvingWindow(vector<Question *> *questions,
                      string outfileName,
                      string timestamp,
                      QWidget *parent = nullptr);
    virtual ~TaskSolvingWindow();

signals:
    void IsClosed();

public slots:
    void next_question_button_clicked();

private:
    string outfileName;
    string timestamp;
    vector<Question *> *questions;
    int question_counter;
    string current_question_type;
    vector<string> given_text_answers;
    vector<vector<int>> given_multi_answers;
    bool rewrite_logfile;

    QVBoxLayout *mainlayout;
    QLabel *InfoLabel;
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
    void checkLogfile();
    void writeLogfile();
    string givenAnswersToSring();
    string getTextAfter(ifstream &infile,
                        string after_this);
};


#endif
