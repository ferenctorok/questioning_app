#ifndef QUESTION_OPTION_H
#define QUESTION_OPTION_H
#include <QWidget>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QTextEdit>


class QuestionOption : public QWidget
{
    Q_OBJECT
public:
    QuestionOption(QWidget *parent = nullptr);
    QuestionOption(QLayout * parent_layout,
                   QWidget *parent = nullptr);
    ~QuestionOption() {};

signals:
    bool clicked();

protected:
    QHBoxLayout *layout;
    QRadioButton *radio_button;
    QTextEdit *text_edit;
};

#endif
