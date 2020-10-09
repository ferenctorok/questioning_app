#include <task_solving.h>


TaskSolvingWindow::TaskSolvingWindow(vector<Question *> *questions,
                                     QWidget *parent):
    QWidget(parent)
{
    this->questions = questions;

    question_counter = 1;

    // setting up the widget (window)
    setAttribute(Qt::WA_DeleteOnClose);
    resize(600, 400);
    setObjectName("task_solving_window");
    setWindowTitle("Feladatsor megoldása");

    // main layout
    mainlayout = set_QVBoxLayout(this, "mainlayout");

    // textedit for questions:
    QuestionLabel = set_QLabel(this, "", "question_label",mainlayout);

    // textedit for answers:
    AnswerTextEdit = set_QTextEdit(this, "answer_textedit",
                                    "Írd ide a választ...", mainlayout);

    // multiple choice radiobuttons with layout:
    MultipleChoiceWidget = set_Qwidget(this, "multiple_choice_widget", mainlayout);
    MultipleChoiceLayout = set_QVBoxLayout(MultipleChoiceWidget, "multiple_choice_layout");

    NextQuestionButton = set_QPushButton(300, 120, this, "next_question_button",
                                         "Következő", "Következő kérdés", mainlayout);
    mainlayout->setAlignment(NextQuestionButton, Qt::AlignHCenter);
}


TaskSolvingWindow::~TaskSolvingWindow()
{
    delete questions;
}


void TaskSolvingWindow::closeEvent(QCloseEvent *event)
{
    emit IsClosed();
    QWidget::closeEvent(event);
}
