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
#include <QPalette>

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




class ResultDetailsWindow: public QWidget
{
    Q_OBJECT

public:
    ResultDetailsWindow(Result *result,
                        QWidget *parent = nullptr);
    ~ResultDetailsWindow() {};

public slots:
    void set_back_state();

private:
    Result *result;

    QVBoxLayout *mainlayout;
    QLabel *InfoLabel;
    QLabel *QuestionLabel;
    QLabel *CorrectAnswerLabel;
    QFrame *MultipleChoiceFrame;
    QVBoxLayout *MultipleChoiceLayout;
    QList<QCheckBox *> answerOptionList;
    QLabel *GivenAnswersLabel;

    void set_up_multiple_choice_frame();
};


class ResultsWindow: public QWidget
{
    Q_OBJECT

public:
    ResultsWindow(vector<Result *> *results,
                  QWidget *parent = nullptr);
    virtual ~ResultsWindow();

public slots:
    void details_button_clicked();

signals:
    void IsClosed();

private:
    vector<Result *> *results;
    ResultDetailsWindow *detail_window;

    QVBoxLayout *mainLayout;
    QHBoxLayout *mainInfoLayout;
    QLabel *mainInfoLabel;
    QLabel *smileyLabel;
    QScrollArea *scrollArea;
    QWidget *ScrollAreaWidget;
    QVBoxLayout *ScrollAreaWidgetLayout;
    QList<QWidget *> *widgetList;
    QList<QPushButton *> *buttonList;
    QList<QLabel *> *labelList;
    QList<QHBoxLayout *> *layoutList;
    QPalette *correctPaletteFirst;
    QPalette *correctPalette;
    QPalette *wrongPalette;

    void closeEvent(QCloseEvent *event);
    void set_up_lists(Result *result);
    string getMainInfoString();
    int getNumOfCorrectAnswers();
    int getNumOfCorrectAnswersFirst();
};
#endif
