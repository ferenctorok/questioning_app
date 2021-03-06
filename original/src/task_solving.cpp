#include <task_solving.h>


const string LOG_FILE = ".logfile";


TaskSolvingWindow::TaskSolvingWindow(vector<Question *> *questions,
                                     string outfileName,
                                     string timestamp,
                                     QWidget *parent):
    QWidget(parent)
{
    this->questions = questions;
    this->outfileName = outfileName;
    this->timestamp = timestamp;

    // setting icon:
    setWindowIcon(QIcon(":/question_mark.ico"));

    // checking logfile: check if the question file has already been opened,
    // and if yes, starting from where it was left last time.
    checkLogfile();

    // if the file has been solved totally previously:
    if (question_counter >= questions->size())
    {
        string message = "A feladatsort már egyszer megoldottad!";
        QMessageBox::information(this, "A feladatsor már kész!", QString::fromStdString(message));
        rewrite_logfile = false;
        close();
    }
    else
    {
        rewrite_logfile = true;
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
}


TaskSolvingWindow::~TaskSolvingWindow()
{
    delete questions;
}


void TaskSolvingWindow::closeEvent(QCloseEvent *event)
{
    if (rewrite_logfile) writeLogfile();
    emit IsClosed();
    QWidget::closeEvent(event);
}


void TaskSolvingWindow::next_question_button_clicked()
{
    Question *question = questions->at(question_counter - 1);
    question->useTrial();

    // logging the given answer for later writing it into the outfile.
    if (question->getType() == "text") given_text_answers.push_back(readTextAnswer());
    else given_multi_answers.push_back(readMultiAnswer());

    // check the question and go on if its correct or if we are out of trials.
    if (isCorrectAnswer() || question->outOfTrials())
    {
        // dialog windows and log writing;
        if (isCorrectAnswer())
        {
            writeResultToFile(question, true);
            correctAnswerDialog();
        }
        else
        {
            writeResultToFile(question, false);
            incorrectAnswerDialog();
        }

        // emptying the logs:
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
    info_string += "\nHátralévő próbálkozások száma: ";
    info_string += to_string(question->getRemainingTrials());
    InfoLabel->setText(QString::fromStdString(info_string));
}


void TaskSolvingWindow::writeResultToFile(Question *question,
                                 bool isCorrect)
{
    // opening file for appending:
    ofstream outfile;
    outfile.open(outfileName, ios_base::app);

    // header:
    outfile << "QUESTION" << question_counter << "/" << questions->size() << endl;
    // correctness:
    write_section(outfile, "correct", to_string(isCorrect));

    // trials and used trials
    string trials_str = to_string(question->getUsedTrials());
    trials_str += ("/" + to_string(question->getNumOfTrials()));
    write_section(outfile, "trials", trials_str);

    // type:
    write_section(outfile, "type", question->getType());

    // question:
    write_section(outfile, "question", question->getQuestion());

    if (question->getType() == "text")
    {
        // real answer:
        write_section(outfile, "real_answer", question->getTextAnswer());

        // given answers:
        outfile << "<given_answers>" << endl;
        for (auto &answer: given_text_answers) outfile << "*" << answer << endl;
        outfile << "</given_answers>" << endl;
    }
    else
    {
        // options:
        outfile << "<answer_options>" << endl;
        for (auto &option: *question->getOptions()) outfile << "*" << option << endl;
        outfile << "</answer_options>" << endl;

        // real answer:
        string real_answer_str = "";
        for (auto &answer: question->getMultiAnswer())
            real_answer_str += (to_string(answer) + ",");
        write_section(outfile, "real_answer", real_answer_str);

        // given answers:
        outfile << "<given_answers>" << endl;
        for (auto &answers_vect: given_multi_answers)
        {
            outfile << "*";
            for (auto &answer: answers_vect) outfile << answer << ",";
            outfile << endl;
        }
        outfile << "</given_answers>" << endl;
    }
    outfile << endl;

    outfile.close();
}


void TaskSolvingWindow::checkLogfile()
{
    question_counter = 0;

    ifstream logfile(LOG_FILE, ios_base::binary);
    if (!logfile)
    {
        ofstream new_logfile(LOG_FILE);
        new_logfile.close();
        logfile.open(LOG_FILE, ios_base::binary);
    }

    // search for the timestamp in the logfile:
    string line;
    size_t pos;
    string timestamp_candidate;
    while (logfile.good())
    {
        // searching for the timestamp:
        timestamp_candidate = getTextAfter(logfile, "timestamp:");
        if (timestamp_candidate == timestamp)
        {
            // setting the question number:
            string question_num_str = getTextAfter(logfile, "question_num:");
            if (question_num_str != "NOT_FOUND") question_counter = stoi(question_num_str);
            else question_counter = 0;

            // setting the used trials:
            int used_trials = 0;
            if (question_counter < questions->size())
            {
                string used_trials_string = getTextAfter(logfile, "num_used_trials:");
                if (question_num_str != "NOT_FOUND") used_trials = stoi(used_trials_string);
                for (int i = 0; i < used_trials; i++) questions->at(question_counter)->useTrial();
            }

            // setting the list of already given aswers:
            if (getTextAfter(logfile, "given_answers:") != "NOT_FOUND"){
                string given_answer_string;
                // reading in the given answer as a string at first:
                for (int i = 0; i < used_trials; i++){
                    given_answer_string = getTextAfter(logfile, "*");
                    // putting it in the vectors according to question type:
                    if (given_answer_string != "NOT_FOUND"){
                        if (questions->at(question_counter)->getType() == "text"){
                            given_text_answers.push_back(given_answer_string);
                        }
                        else{
                            given_multi_answers.push_back(get_multi_answers_from_string(given_answer_string));
                        }
                    }
                }
            }

            break;
        }
    }
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


void TaskSolvingWindow::writeLogfile()
{
    ifstream logfile(LOG_FILE, ios_base::binary);
    if (logfile)
    {
        // search for the timestamp in the logfile:
        string line;
        size_t pos;
        string timestamp_candidate;
        bool timestamp_found = false;
        while (logfile.good())
        {
            // checking whether there is already a log with this timestamp:
            timestamp_candidate = getTextAfter(logfile, "timestamp:");
            if (timestamp_candidate == timestamp)
            {
                timestamp_found = true;

                // copying the parts until this point into a string.
                streampos strpos = logfile.tellg();
                string copy_string;
                copy_string.resize(strpos);
                ifstream readfile(LOG_FILE);
                readfile.read(&copy_string[0], strpos);

                // adding the new data to the string.
                copy_string += "question_num:" + to_string(question_counter - 1) + "\n";
                // this is needed because question_counter is also increased one last time after the last question.
                // if this modification would not be here, it would cause out of range errors for the vectors:
                if (question_counter > questions->size()) question_counter = questions->size();
                copy_string += "num_used_trials:" + to_string(questions->at(question_counter - 1)->getUsedTrials()) + "\n";
                copy_string += "given_answers:\n";
                copy_string += givenAnswersToSring();
                copy_string += "\n";

                // skipping the old entries about this timestamp in the original file:
                do {
                    strpos = logfile.tellg();
                    getline(logfile, line);
                }
                while ((line.find("timestamp:") == string::npos) && logfile.good());

                // copying the rest of the file:
                if (logfile.good()){
                    // setting back the stream before "timestamp:" for further reading.
                    logfile.seekg(strpos);
                    while (logfile.good())
                    {
                        getline(logfile, line);
                        copy_string += line + "\n";
                    }
                }
                // deleting last new line from the end:
                copy_string = copy_string.substr(0, copy_string.length() - 1);

                // writing the new file:
                logfile.close();
                ofstream outfile(LOG_FILE);
                outfile << copy_string;

                break;
            }
        }

        if (!timestamp_found)
        {
            logfile.close();
            ofstream logoutfile(LOG_FILE, ios_base::app);
            logoutfile << "timestamp:" << timestamp << endl;
            logoutfile << "question_num:" << question_counter - 1 << endl;
            // this is needed because question_counter is also increased one last time after the last question.
            // if this modification would not be here, it would cause out of range errors for the vectors:
            if (question_counter > questions->size()) question_counter = questions->size();
            logoutfile << "num_used_trials:" << questions->at(question_counter - 1)->getUsedTrials() << endl;
            logoutfile << "given_answers:" << endl;
            logoutfile << givenAnswersToSring();
            logoutfile << endl;
        }

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
