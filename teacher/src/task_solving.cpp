#include <task_solving.h>


TaskSolvingWindow::TaskSolvingWindow(vector<Question *> *questions,
                                     QWidget *parent):
    QWidget(parent)
{
    this->questions = questions;

    question_counter = 0;
    current_question_type = "";

    // setting font size:
    this->setFont(QFont("Times", 12));

    // setting icon:
    setWindowIcon(QIcon(":/question_mark.ico"));

    // setting up the widget (window)
    setAttribute(Qt::WA_DeleteOnClose);
    resize(800, 600);
    setObjectName("task_solving_window");
    setWindowTitle("Feladatsor megoldása");

    // main layout
    mainlayout = set_QVBoxLayout(this, "mainlayout");

    // info label:
    InfoLabel = set_QLabel(750, this, "", "info_label", mainlayout);
    InfoLabel->setMaximumHeight(100);

    // textedit for questions:
    QuestionLabel = set_QLabel(750, this, "", "question_label", mainlayout);

    // textedit for answers:
    AnswerTextEdit = set_QTextEdit(this, "answer_textedit",
                                    "Írd ide a választ...", mainlayout);

    // multiple choice radiobuttons with layout:
    MultipleChoiceFrame = set_QFrame(this, "multiple_choice_frame", mainlayout);
    MultipleChoiceLayout = set_QVBoxLayout(MultipleChoiceFrame, "multiple_choice_layout");

    // Layout of the buttons:
    ButtonLayout = set_QHBoxLayout(nullptr, "button_layout");
    mainlayout->addLayout(ButtonLayout);

    // Button for displaying the previous question:
    PreviousButton = set_QPushButton(100, 40, this, "previous_button",
                                         "Előző", "Előző kérdés mutatása", ButtonLayout);
    connect(PreviousButton, SIGNAL(clicked()), this, SLOT(previous_button_clicked()));
    PreviousButton->setEnabled(false);

    // Button for checking the correctness of the answers:
    CorrectionButton = set_QPushButton(100, 40, this, "correction_button",
                                         "Ellenőrzés", "Kérdés ellenőrzése", ButtonLayout);
    connect(CorrectionButton, SIGNAL(clicked()), this, SLOT(correction_button_clicked()));

    // Button for displaying the next question:
    NextButton = set_QPushButton(100, 40, this, "next_button",
                                         "Következő", "Következő kérdés mutatása", ButtonLayout);
    connect(NextButton, SIGNAL(clicked()), this, SLOT(next_button_clicked()));
    if (questions->size() <= 1) NextButton->setEnabled(false);

    // displaying the first question:
    displayQuestion();
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


void TaskSolvingWindow::previous_button_clicked()
{
    NextButton->setEnabled(true);
    if (question_counter - 1 >= 0) question_counter--;
    displayQuestion();
    if (question_counter <= 0) PreviousButton->setEnabled(false);
}


void TaskSolvingWindow::next_button_clicked()
{
    PreviousButton->setEnabled(true);
    if (question_counter + 1 < questions->size()) question_counter++;
    displayQuestion();
    if (question_counter >= (questions->size() - 1)) NextButton->setEnabled(false);
}


void TaskSolvingWindow::correction_button_clicked()
{
    if (isCorrectAnswer()) correctAnswerDialog();
    else incorrectAnswerDialog();
}


void TaskSolvingWindow::displayQuestion()
{
    Question *question = questions->at(question_counter);
    current_question_type = question->getType();

    // displaying the question and the info:
    refreshInfoLabel(question);
    QuestionLabel->setText(QString::fromStdString(question->getQuestion()));

    if (current_question_type == "text")
    {
        MultipleChoiceFrame->hide();
        AnswerTextEdit->clear();
        AnswerTextEdit->show();
    }
    else
    {
        AnswerTextEdit->hide();
        MultipleChoiceFrame->show();
        clearOptionList();
        // adding every option to the list and displaying it.
        for (auto &option: *question->getOptions())
        {
            answerOptionList.append(new QCheckBox());
            answerOptionList.last()->setParent(MultipleChoiceFrame);
            answerOptionList.last()->setText(QString::fromStdString(option));
            MultipleChoiceLayout->addWidget(answerOptionList.last());
        }
    }
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
        return questions->at(question_counter)->isCorrectAnswer(answer);
    }
    else
    {
        vector<int> answer = readMultiAnswer();
        return questions->at(question_counter)->isCorrectAnswer(answer);
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
    // removing internal new lines:
    pos = 0;
    while (str.find_first_of("\n", pos) != string::npos){
        pos = str.find_first_of("\n", pos);
        str.erase(pos, 1);
    }
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
    string info_string = "Kérdés ";
    info_string += to_string(question->getQuestionNum() + 1) + "/";
    info_string += to_string(questions->size());
    info_string += "\nPróbálkozások száma: ";
    info_string += to_string(question->getRemainingTrials());
    InfoLabel->setText(QString::fromStdString(info_string));
}


string TaskSolvingWindow::getTextAfter(ifstream &infile,
                                       string after_this)
{
    string line;
    getline(infile, line);

    size_t pos = line.find(after_this);
    if (pos != string::npos)
    {
        string return_string = line.substr(pos + after_this.length());
        return_string = return_string.substr(0, return_string.length() - 1);
        return return_string;
    }
    else
    {
        return "NOT_FOUND";
    }
}


string TaskSolvingWindow::givenAnswersToSring()
{
    string str = "";
    if (current_question_type == "text")
        for (auto answer: given_text_answers) str += "*" + answer + "\n";
    else
    {
        for (auto answer: given_multi_answers){
            str += "*";
            for (auto num: answer) str += to_string(num) + ",";
            str += "\n";
        }
    }
    return str;
}
