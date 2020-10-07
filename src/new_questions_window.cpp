#include <iostream>

#include <new_questions.h>
#include <utils.h>


NewQuestionsWindow::NewQuestionsWindow(QString filename,
                                       QWidget *parent):
        QWidget(parent)
{
    // setting up output file
    this->filename = filename.toStdString();

    // setting up the widget (window)
    setAttribute(Qt::WA_DeleteOnClose);
    resize(600, 400);
    setObjectName("new_questions_window");
    setWindowTitle("új kérdéssor összeállítása");

    // main layout
    mainlayout = set_QVBoxLayout(this, "mainlayout");

    // question type choosing layout
    questionTypeLayout = set_QHBoxLayout(nullptr, "question_type_layout");
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
    add_option_to_list(answerOptionList, MultipleChoiceWidget, 3);
    add_OptionList_to_layout(answerOptionList, MultipleChoiceLayout);

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

    // new question and save and end buttons and their layout:
    BottomButtonsLayout = new QHBoxLayout();
    mainlayout->addLayout(BottomButtonsLayout);
    NewQuestionButton = set_QPushButton(200, 150, this, "new_question_button",
                                        "Új kérdés", "Új kérdés hozzáadása", BottomButtonsLayout);
    connect(NewQuestionButton, SIGNAL(clicked()), this, SLOT(add_new_question()));
    SaveAndQuitButton = set_QPushButton(200, 150, this, "save_and_quit_button",
                                        "Befejezés", "Befejezés és kérdések mentése", BottomButtonsLayout);
    connect(SaveAndQuitButton, SIGNAL(clicked()), this, SLOT(save_and_quit()));
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
    add_option_to_list(answerOptionList, MultipleChoiceWidget);
    MultipleChoiceLayout->insertWidget(answerOptionList.count() - 1, answerOptionList.last());
}


void NewQuestionsWindow::del_multi_choice_option()
{
    if (!answerOptionList.empty())
    {
        MultipleChoiceLayout->removeWidget(answerOptionList.last());
        delete answerOptionList.last();
        answerOptionList.removeLast();
    }
}


void NewQuestionsWindow::add_new_question()
{
    save_question();

    QuestionTextEdit->setText("");
    if (textAnswerRB->isChecked())
    {
        AnswerTextEdit->setText("");
    }
    else
    {
        // deleting the answer options and recreating 3 new:
        while (!answerOptionList.empty())
        {
            MultipleChoiceLayout->removeWidget(answerOptionList.last());
            delete answerOptionList.last();
            answerOptionList.removeLast();
        }
        add_option_to_list(answerOptionList, MultipleChoiceWidget, 3);
        add_OptionList_to_layout(answerOptionList, MultipleChoiceLayout);
    }
}


void NewQuestionsWindow::save_and_quit()
{
    save_question();
    close();
}


void NewQuestionsWindow::save_question()
{
    ofstream outfile(filename, ios_base::app);
    if (outfile.is_open())
    {
        outfile << "yolo" << endl;
        outfile << "yololo" << endl;
        outfile.close();
    }
}

