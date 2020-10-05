#ifndef QUESTION_OPTION_H
#define QUESTION_OPTION_H
#include <QWidget>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QTextEdit>


class AnswerOption : public QWidget
{
    Q_OBJECT
public:
    AnswerOption(QWidget *parent = nullptr);
    AnswerOption(QLayout * parent_layout,
                 QWidget *parent = nullptr);
    ~AnswerOption() {};

    bool isChecked();

signals:
    bool clicked();

protected:
    QHBoxLayout *layout;
    QRadioButton *radio_button;
    QTextEdit *text_edit;
};

#endif
