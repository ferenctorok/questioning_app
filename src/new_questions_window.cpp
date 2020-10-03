#include <iostream>
#include <new_questions.h>


NewQuestionsWindow::NewQuestionsWindow(QWidget *parent):
        QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    centralwidget = new QWidget(this);
    mainlayout = new QVBoxLayout(centralwidget);
    QuestionTypeLayout = new QHBoxLayout(centralwidget);
    MultipleChoiceLayout = new QVBoxLayout(centralwidget);
    multipleChoiceRB = new QRadioButton(centralwidget);
    textAnswearRB = new QRadioButton(centralwidget);
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
