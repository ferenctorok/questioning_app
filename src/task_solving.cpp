#include <task_solving.h>


TaskSolvingWindow::TaskSolvingWindow(vector<Question *> *questions,
                                     QWidget *parent):
    QWidget(parent)
{
    this->questions = questions;

    question_counter = 0;

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
    connect(NextQuestionButton, SIGNAL(clicked()), this, SLOT(next_question_button_clicked()));

    // displaying the first question:
    displayNextQuestion();
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


void TaskSolvingWindow::next_question_button_clicked()
{
    if (question_counter <= questions->size() - 1)
    {
        displayNextQuestion();
        if (question_counter == questions->size())
        {
            NextQuestionButton->setText("Befejezés");
            NextQuestionButton->setToolTip("Kérdéssor Befejezése");
        }
    }
    else close();
}

void TaskSolvingWindow::displayNextQuestion()
{
    Question *question = questions->at(question_counter);

    QuestionLabel->setText(QString::fromStdString(question->getQuestion()));
    if (question->getType() == "text")
    {
        MultipleChoiceWidget->hide();
        AnswerTextEdit->show();
    }
    else
    {
        for (auto &option: *question->getOptions()) cout << option << endl;

        AnswerTextEdit->hide();
        MultipleChoiceWidget->show();
        clearOptionList();
        for (auto &option: *question->getOptions())
        {
            answerOptionList.append(new QCheckBox());
            answerOptionList.last()->setParent(MultipleChoiceWidget);
            answerOptionList.last()->setText(QString::fromStdString(option));
            MultipleChoiceLayout->addWidget(answerOptionList.last());
        }
    }

    question_counter++;
}


void TaskSolvingWindow::clearOptionList()
{
    for (auto &option: answerOptionList)
    {
        MultipleChoiceLayout->removeWidget(option);
        delete option;
    }
    answerOptionList.clear();
}
