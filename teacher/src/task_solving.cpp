#include <task_solving.h>


TaskSolvingWindow::TaskSolvingWindow(vector<Question *> *questions,
                                     QWidget *parent):
    QWidget(parent)
{
    this->questions = questions;

    question_counter = 0;
    current_question_type = "";

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

    // logging the given answer for later writing it into the outfile.
    if (question->getType() == "text") given_text_answers.push_back(readTextAnswer());
    else given_multi_answers.push_back(readMultiAnswer());

    // check the question and go on if its correct or if we are out of trials.
    if (isCorrectAnswer())
    {
        correctAnswerDialog();

        // emptying the vectors of given answers:
        given_text_answers.clear();
        given_multi_answers.clear();

        // displaying next question:
        if (question_counter <= questions->size() - 1)
        {
            displayNextQuestion();
            if (question_counter == questions->size())
            {
                NextQuestionButton->setText("Befejezés");
                NextQuestionButton->setToolTip("Kérdéssor Befejezése");
            }
        }
        else
        {
            question_counter ++;
            close();
        }
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
