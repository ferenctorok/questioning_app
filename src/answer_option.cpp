#include <answer_option.h>
#include <utils.h>


AnswerOption::AnswerOption(QWidget *parent):
    QWidget(parent)
{
    layout = set_QHBoxLayout(this, "layout");
    radio_button = set_QRadioButton(this, "radio_button", "", layout);
    text_edit = set_QTextEdit(2000, 40, this, "text_edit",
                              "válasz lehetőség...", layout);
    connect(radio_button, SIGNAL(clicked()), this, SIGNAL(clicked()));
}


AnswerOption::AnswerOption(QLayout *parent_layout,
                               QWidget *parent):
    AnswerOption(parent)
{
    parent_layout->addWidget(this);
}


bool AnswerOption::isChecked()
{
    return radio_button->isChecked();
}
