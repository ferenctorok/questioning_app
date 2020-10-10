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

    // info label:
    InfoLabel = set_QLabel(this, "", "info_label", mainlayout);

    // textedit for questions:
    QuestionLabel = set_QLabel(this, "", "question_label", mainlayout);

    // textedit for answers:
    AnswerTextEdit = set_QTextEdit(this, "answer_textedit",
                                    "Írd ide a választ...", mainlayout);

    // multiple choice radiobuttons with layout:
    MultipleChoiceWidget = set_Qwidget(this, "multiple_choice_widget", mainlayout);
    MultipleChoiceLayout = set_QVBoxLayout(MultipleChoiceWidget, "multiple_choice_layout");

    NextQuestionButton = set_QPushButton(100, 40, this, "next_question_button",
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
    Question *question = questions->at(question_counter - 1);
    question->useTrial();
    if (isCorrectAnswer() || question->outOfTrials())
    {
        if (question->outOfTrials()) incorrectAnswerDialog();
        else correctAnswerDialog();
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
    else
    {
        incorrectAnswerDialog();
        refreshInfoLabel(question);
    }
}


void TaskSolvingWindow::displayNextQuestion()
{
    Question *question = questions->at(question_counter);
    current_question_type = question->getType();

    // displaying the question and the info:
    refreshInfoLabel(question);
    QuestionLabel->setText(QString::fromStdString(question->getQuestion()));

    if (current_question_type == "text")
    {
        MultipleChoiceWidget->hide();
        AnswerTextEdit->clear();
        AnswerTextEdit->show();
    }
    else
    {
        AnswerTextEdit->hide();
        MultipleChoiceWidget->show();
        clearOptionList();
        // adding every option to the ist and displaying it.
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


bool TaskSolvingWindow::isCorrectAnswer()
{
    if (current_question_type == "text")
    {
        string answer = readTextAnswer();
        return questions->at(question_counter - 1)->isCorrectAnswer(answer);
    }
    else
    {
        vector<int> answer = readMultiAnswer();
        return questions->at(question_counter - 1)->isCorrectAnswer(answer);
    }
}


string TaskSolvingWindow::readTextAnswer()
{
    string str = AnswerTextEdit->toPlainText().toStdString();
    string whitespaces =  " \t\f\v\n\r";
    // removing extra spaces at the beginning:
    size_t pos = str.find_first_not_of(whitespaces);
    str.erase(0, pos);
    // removing extra spaces at the end:
    pos = str.find_last_not_of(whitespaces);
    str.erase(pos + 1, string::npos);
    return str;
}


vector<int> TaskSolvingWindow::readMultiAnswer()
{
    vector<int> answer;
    for (int i = 0; i < answerOptionList.count(); i++)
    {
        if (answerOptionList.at(i)->isChecked()) answer.push_back(i);
    }
    return answer;
}


void TaskSolvingWindow::incorrectAnswerDialog()
{
    string message = "Sajnos nem ez a jó válasz!";
    QMessageBox::critical(this, "Hibás válasz", QString::fromStdString(message));
}


void TaskSolvingWindow::correctAnswerDialog()
{
    string message = "Helyes válasz!!!";
    QMessageBox::information(this, "Siker!", QString::fromStdString(message));
}


void TaskSolvingWindow::refreshInfoLabel(Question *question)
{
    string info_string = to_string(question->getQuestionNum());
    info_string += ". kérdés\n Hátralévő próbálkozások száma: ";
    info_string += to_string(question->getRemainingTrials());
    InfoLabel->setText(QString::fromStdString(info_string));
}
