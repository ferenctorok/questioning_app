#include <question_option.h>
#include <utils.h>


QuestionOption::QuestionOption(QWidget *parent):
    QWidget(parent)
{
    layout = set_QHBoxLayout(this, "layout");
    radio_button = set_QRadioButton(this, "radio_button", "", layout);
    text_edit = set_QTextEdit(this, "text_edit",
                              "válasz lehetőség...", layout);
}

QuestionOption::QuestionOption(QLayout *parent_layout,
                               QWidget *parent):
    QuestionOption(parent)
{
    parent_layout->addWidget(this);
}
