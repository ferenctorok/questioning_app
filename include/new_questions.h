#ifndef NEW_QUESTIONS_H
#define NEW_QUESTIONS_H
#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QList>
#include <QCloseEvent>
#include <QTextEdit>
#include <vector>
#include <iostream>
#include <fstream>

#include <answer_option.h>
#include <question_utils.h>

using namespace std;


class NewQuestionsWindow: public QWidget
{
    Q_OBJECT

public:
    NewQuestionsWindow(QString filename,
                       QWidget *parent = nullptr);
    virtual ~NewQuestionsWindow() {};

public slots:
    void multiChRB_clicked();
    void textAnsRb_clicked();
    void add_multi_choice_option();
    void del_multi_choice_option();
    void add_new_question();
    void save_and_quit();

signals:
    void IsClosed();

private:
    string filename;
    int question_counter;
    QVBoxLayout *mainlayout;
    QHBoxLayout *questionTypeLayout;
    QRadioButton *multipleChoiceRB;
    QRadioButton *textAnswerRB;
    QTextEdit *QuestionTextEdit;
    QTextEdit *AnswerTextEdit;
    QWidget *MultipleChoiceWidget;
    QVBoxLayout *MultipleChoiceLayout;
    QList<AnswerOption *> answerOptionList;
    QHBoxLayout *moreOrLessLayout;
    QPushButton *moreOptionsButton;
    QPushButton *lessOptionsButton;
    QHBoxLayout *BottomButtonsLayout;
    QPushButton *NewQuestionButton;
    QPushButton *SaveAndQuitButton;

    void closeEvent(QCloseEvent *event);
    void save_question();
};
#endif
