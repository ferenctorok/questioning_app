#ifndef NEW_QUESTIONS_H
#define NEW_QUESTIONS_H
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <time.h>

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QList>
#include <QCloseEvent>
#include <QTextEdit>
#include <QSpinBox>
#include <QLabel>
#include <QDir>

#include <answer_option.h>

using namespace std;


class NewQuestionsWindow: public QWidget
{
    Q_OBJECT

public:
    NewQuestionsWindow(string filename,
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
    QVBoxLayout *mainlayout;
    QHBoxLayout *questionTypeLayout;
    QRadioButton *multipleChoiceRB;
    QRadioButton *textAnswerRB;
    QHBoxLayout *numberOfTrialsLayout;
    QLabel *numberOfTrialsLabel;
    QSpinBox *numberOfTrialsSpinBox;
    QTextEdit *QuestionTextEdit;
    QTextEdit *AnswerTextEdit;
    QWidget *MultipleChoiceWidget;
    QHBoxLayout *MultipleChoiceMainLayout;
    QVBoxLayout *MultipleChoiceLayout;
    QList<AnswerOption *> answerOptionList;
    QVBoxLayout *moreOrLessLayout;
    QPushButton *moreOptionsButton;
    QPushButton *lessOptionsButton;
    QHBoxLayout *BottomButtonsLayout;
    QPushButton *NewQuestionButton;
    QPushButton *SaveAndQuitButton;

    void closeEvent(QCloseEvent *event);
    void save_question();
    string read_from_textedit(QTextEdit *textEdit);
    string getTimestamp();
};
#endif
