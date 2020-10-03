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

    // radio button for choosing multiple choice question
    multipleChoiceRB = set_QRadioButton(300, 100, this, "multiple_choice_rb",
                                        "Feleletválasztós", questionTypeLayout);
    connect(multipleChoiceRB, SIGNAL(clicked()), this, SLOT(multiChRB_clicked()));
    multipleChoiceRB->setChecked(true);

    // radio button for choosing typed answer question
    textAnswerRB = set_QRadioButton(this, "text_answer_rb",
                                        "Szöveges válasz", questionTypeLayout);
    connect(textAnswerRB, SIGNAL(clicked()), this, SLOT(textAnsRb_clicked()));

    // textedit for questions:
    QuestionTextEdit = set_QTextEdit(this, "question_textedit",
                                     "Írd ide a kérdést...", mainlayout);

    // textedit for answers:
    QuestionTextEdit = set_QTextEdit(this, "answer_textedit",
                                    "Írd ide a választ...", mainlayout);
}

NewQuestionsWindow::~NewQuestionsWindow()
{

}

void NewQuestionsWindow::closeEvent(QCloseEvent *event)
{
    std::cout << "closeEvent() is called\n";
    emit IsClosed();
    QWidget::closeEvent(event);
}

void NewQuestionsWindow::multiChRB_clicked()
{

}

void NewQuestionsWindow::textAnsRb_clicked()
{

}

