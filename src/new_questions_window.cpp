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

    // radio button for choosing typed answear question
    textAnswearRB = set_QRadioButton(this, "text_answear_rb",
                                        "Szöveges válasz", questionTypeLayout);


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
