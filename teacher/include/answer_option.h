#ifndef QUESTION_OPTION_H
#define QUESTION_OPTION_H
#include <iostream>
#include <QWidget>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QTextEdit>

using namespace std;


class AnswerOption : public QWidget
{
    Q_OBJECT
public:
    AnswerOption(QWidget *parent = nullptr);
    AnswerOption(QLayout * parent_layout,
                 QWidget *parent = nullptr);
    ~AnswerOption() {};

    string get_text();
    bool isChecked();

signals:
    bool clicked();

protected:
    QHBoxLayout *layout;
    QRadioButton *radio_button;
    QTextEdit *text_edit;
};

#endif
