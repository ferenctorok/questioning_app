#include <iostream>

#include <new_questions.h>
#include <utils.h>


NewQuestionsWindow::NewQuestionsWindow(QString filename,
                                       QWidget *parent):
        QWidget(parent)
{
    // setting up output file
    this->filename = filename.toStdString();
    ofstream outfile(this->filename);
    outfile << "timestamp:" << getTimestamp() << endl << endl;
    outfile.close();

    // setting up the widget (window)
    setAttribute(Qt::WA_DeleteOnClose);
    resize(800, 600);
    setObjectName("new_questions_window");
    setWindowTitle("új kérdéssor összeállítása");

    // main layout
    mainlayout = set_QVBoxLayout(this, "mainlayout");

    // question type choosing layout and radio buttons:
    questionTypeLayout = set_QHBoxLayout(nullptr, "question_type_layout");
    mainlayout->addLayout(questionTypeLayout);
    textAnswerRB = set_QRadioButton(this, "text_answer_rb",
                                        "Szöveges válasz", questionTypeLayout);
    connect(textAnswerRB, SIGNAL(clicked()), this, SLOT(textAnsRb_clicked()));
    textAnswerRB->setChecked(true);
    multipleChoiceRB = set_QRadioButton(300, 100, this, "multiple_choice_rb",
                                        "Feleletválasztós", questionTypeLayout);
    connect(multipleChoiceRB, SIGNAL(clicked()), this, SLOT(multiChRB_clicked()));

    // number of trials layout, label and spinbox
    numberOfTrialsLayout = set_QHBoxLayout(nullptr, "number_of_questions_layout");
    mainlayout->addLayout(numberOfTrialsLayout);
    numberOfTrialsLabel = set_QLabel(300, this, "Próbálkozások száma:",
                                     "number_of_trials_layout", numberOfTrialsLayout);
    numberOfTrialsSpinBox = set_QSpinBox(this, "number_of_trials_spin_box",
                                         numberOfTrialsLayout);
    numberOfTrialsSpinBox->setValue(3);

    // textedit for questions:
    QuestionTextEdit = set_QTextEdit(this, "question_textedit",
                                     "Írd ide a kérdést...", mainlayout);

    // textedit for answers:
    AnswerTextEdit = set_QTextEdit(this, "answer_textedit",
                                    "Írd ide a választ...", mainlayout);

    // widget for the multiple choice questions:
    MultipleChoiceWidget = set_Qwidget(this, "multiple_choice_widget", mainlayout);
    MultipleChoiceWidget->hide();
    // main layout of the multiple questions widget.
    MultipleChoiceMainLayout = set_QHBoxLayout(MultipleChoiceWidget, "multiple_choice_main_layout");
    // vertical layout of the radio buttons.
    MultipleChoiceLayout = new QVBoxLayout();
    MultipleChoiceMainLayout->addLayout(MultipleChoiceLayout);
    // adding options (radio buttons with text edit) to the vertical layout:
    add_option_to_list(answerOptionList, MultipleChoiceWidget, 3);
    add_OptionList_to_layout(answerOptionList, MultipleChoiceLayout);

    // buttons for more or less options:
    moreOrLessLayout = new QVBoxLayout();
    moreOrLessLayout->setAlignment(Qt::AlignVCenter);
    MultipleChoiceMainLayout->addLayout(moreOrLessLayout);
    moreOptionsButton =set_QPushButton(100, 30, MultipleChoiceWidget,
                                       "more_options_button", "Több",
                                       "Még egy opció hozzáadása", moreOrLessLayout);
    connect(moreOptionsButton, SIGNAL(clicked()), this, SLOT(add_multi_choice_option()));
    lessOptionsButton =set_QPushButton(100, 30, MultipleChoiceWidget,
                                       "less_options_button", "Kevesebb",
                                       "Utolsó opció elvétele", moreOrLessLayout);
    connect(lessOptionsButton, SIGNAL(clicked()), this, SLOT(del_multi_choice_option()));

    // new question and save and end buttons and their layout:
    BottomButtonsLayout = new QHBoxLayout();
    mainlayout->addLayout(BottomButtonsLayout);
    NewQuestionButton = set_QPushButton(150, 30, this, "new_question_button",
                                        "Új kérdés", "Új kérdés hozzáadása", BottomButtonsLayout);
    connect(NewQuestionButton, SIGNAL(clicked()), this, SLOT(add_new_question()));
    SaveAndQuitButton = set_QPushButton(150, 30, this, "save_and_quit_button",
                                        "Befejezés", "Befejezés és kérdések mentése", BottomButtonsLayout);
    connect(SaveAndQuitButton, SIGNAL(clicked()), this, SLOT(save_and_quit()));
}


void NewQuestionsWindow::closeEvent(QCloseEvent *event)
{
    save_question();
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
        MultipleChoiceLayout->removeItem(moreOrLessLayout);
        add_OptionList_to_layout(answerOptionList, MultipleChoiceLayout);
        MultipleChoiceLayout->addLayout(moreOrLessLayout);
    }
}


void NewQuestionsWindow::save_and_quit()
{
    close();
}


void NewQuestionsWindow::save_question()
{
    if (!QuestionTextEdit->toPlainText().isEmpty())
    {
        ofstream outfile(filename, ios_base::app);

        if (outfile.is_open())
        {
            outfile << "QUESTION" << endl;
            outfile << "trials:" << numberOfTrialsSpinBox->value() << endl;
            outfile << "type:";
            if (textAnswerRB->isChecked()) outfile << "text" << endl;
            else outfile << "multi" << endl;
            outfile << "question:";
            outfile << read_from_textedit(QuestionTextEdit) << endl;

            if (textAnswerRB->isChecked())
            {
                outfile << "answer:";
                outfile << read_from_textedit(AnswerTextEdit) << endl;
            }
            else
            {
                int i = 0;
                vector<int> answers;
                outfile << "answer_options:" << endl;
                for (auto &option: answerOptionList)
                {
                    if (option->get_text() != "")
                    {
                        outfile << "*" << option->get_text() << endl;
                        if (option->isChecked()) answers.push_back(i);
                        i++;
                    }
                }
                outfile << "answers:";
                for (auto &answer: answers) outfile << to_string(answer) << ",";
                outfile << endl;
            }
            outfile << endl;
            outfile.close();
        }
    }
}


string NewQuestionsWindow::read_from_textedit(QTextEdit *textEdit)
{
    string str = textEdit->toPlainText().toStdString();
    replace(str.begin(), str.end(), '\n', ' ');
    return str;
}


string NewQuestionsWindow::getTimestamp()
{
    char stamp[15];
    time_t t = time(0);
    strftime(stamp, sizeof(stamp), "%Y%m%d%H%M%S", gmtime(&t));
    return stamp;
}

