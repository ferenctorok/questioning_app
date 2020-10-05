#include <iostream>

#include <new_questions.h>
#include <utils.h>


NewQuestionsWindow::NewQuestionsWindow(QWidget *parent):
        QWidget(parent)
{
    // delete this widget when closed.
    setAttribute(Qt::WA_DeleteOnClose);
    this->resize(600, 400);
    this->setObjectName("new_questions_window");
    this->setWindowTitle("új kérdéssor összeállítása");

    // main layout
    mainlayout = set_QVBoxLayout(this, "mainlayout");

    // question type choosing layout
    questionTypeLayout = set_QHBoxLayout(this, "question_type_layout");
    mainlayout->addLayout(questionTypeLayout);

    // radio button for choosing typed answer question
    textAnswerRB = set_QRadioButton(this, "text_answer_rb",
                                        "Szöveges válasz", questionTypeLayout);
    connect(textAnswerRB, SIGNAL(clicked()), this, SLOT(textAnsRb_clicked()));
    textAnswerRB->setChecked(true);

    // radio button for choosing multiple choice question
    multipleChoiceRB = set_QRadioButton(300, 100, this, "multiple_choice_rb",
                                        "Feleletválasztós", questionTypeLayout);
    connect(multipleChoiceRB, SIGNAL(clicked()), this, SLOT(multiChRB_clicked()));

    // textedit for questions:
    QuestionTextEdit = set_QTextEdit(this, "question_textedit",
                                     "Írd ide a kérdést...", mainlayout);

    // textedit for answers:
    AnswerTextEdit = set_QTextEdit(this, "answer_textedit",
                                    "Írd ide a választ...", mainlayout);

    // multiple choice radiobuttons with layout:
    MultipleChoiceWidget = set_Qwidget(this, "multiple_choice_widget", mainlayout);
    MultipleChoiceWidget->hide();
    MultipleChoiceLayout = set_QVBoxLayout(MultipleChoiceWidget, "multiple_choice_layout");
    add_RBs_to_list(answearRBlist, MultipleChoiceWidget, 3);
    add_QList_to_layout(answearRBlist, MultipleChoiceLayout);

    // buttons for more or less options:
    moreOrLessLayout = new QHBoxLayout();
    MultipleChoiceLayout->addLayout(moreOrLessLayout);
    moreOptionsButton =set_QPushButton(150, 80, MultipleChoiceWidget,
                                       "more_options_button", "Több",
                                       "Még egy opció hozzáadása", moreOrLessLayout);
    connect(moreOptionsButton, SIGNAL(clicked()), this, SLOT(add_multi_choice_option()));
    lessOptionsButton =set_QPushButton(150, 80, MultipleChoiceWidget,
                                       "less_options_button", "Kevesebb",
                                       "Utolsó opció elvétele", moreOrLessLayout);
    connect(lessOptionsButton, SIGNAL(clicked()), this, SLOT(del_multi_choice_option()));
}

void NewQuestionsWindow::closeEvent(QCloseEvent *event)
{
    std::cout << "closeEvent() is called\n";
    emit IsClosed();
    QWidget::closeEvent(event);
}

void NewQuestionsWindow::multiChRB_clicked()
{
    AnswerTextEdit->hide();
    MultipleChoiceWidget->show();
}

void NewQuestionsWindow::textAnsRb_clicked()
{
    MultipleChoiceWidget->hide();
    AnswerTextEdit->show();
}

void NewQuestionsWindow::add_multi_choice_option()
{
    add_RBs_to_list(answearRBlist, MultipleChoiceWidget);
    MultipleChoiceLayout->insertWidget(answearRBlist.count() - 1, answearRBlist.last());
}

void NewQuestionsWindow::del_multi_choice_option()
{
    if (!answearRBlist.empty())
    {
        MultipleChoiceLayout->removeWidget(answearRBlist.last());
        delete answearRBlist.last();
        answearRBlist.removeLast();
    }
}

