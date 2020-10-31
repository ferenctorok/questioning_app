#include <results.h>


ResultDetailsWindow::ResultDetailsWindow(Result *result,
                                         QWidget *parent):
    QWidget(parent)
{
    this->result = result;

    // setting icon:
    setWindowIcon(QIcon(":/question_mark.ico"));

    // setting up the widget (window)
    setAttribute(Qt::WA_DeleteOnClose);
    resize(600, 400);
    setObjectName("result_detail_window");
    string title = "Feladat " + result->question_number;
    setWindowTitle(QString::fromStdString(title));

    // main layout
    mainlayout = set_QVBoxLayout(this, "mainlayout");

    // info label:
    InfoLabel = set_QLabel(550, this, "", "info_label", mainlayout);
    InfoLabel->setMaximumHeight(100);
    string info_text = "Feladat " + result->question_number + "\n";
    info_text += "Megoldás: ";
    if (result->correct) info_text += "JÓ\n";
    else info_text += "ROSSZ\n";
    info_text += "próbálkozások száma: " + result->trials;
    InfoLabel->setText(QString::fromStdString(info_text));

    // question:
    string question_text = "Kérdés: " + result->question;
    QuestionLabel = set_QLabel(550, this, QString::fromStdString(question_text),
                               "", mainlayout);

    // correct answers:
    if (result->type == "text")
    {
        string answer_text = "Helyes válasz:\n\t" + result->real_answer;
        CorrectAnswerLabel = set_QLabel(550, this, QString::fromStdString(answer_text),
                                        "correct_answer_label", mainlayout);
    }
    else
    {
        set_up_multiple_choice_frame();
    }

    // given answers:
    GivenAnswersLabel = set_QLabel(550, this, "", "given_answers_label", mainlayout);
    string given_answers = "Adott válaszok:\n";
    for (auto &answer: result->given_answers){
        // cutting the last comma for multiple choice answers:
        if (result->type == "multi") answer = answer.substr(0, answer.length() - 1);
        // extending the string:
        given_answers += "\t" + answer + "\n";
    }
    GivenAnswersLabel->setText(QString::fromStdString(given_answers));
}


void ResultDetailsWindow::set_up_multiple_choice_frame()
{
    MultipleChoiceFrame = set_QFrame(this, "multiple_choice_frame", mainlayout);
    MultipleChoiceLayout = set_QVBoxLayout(MultipleChoiceFrame, "multiple_choice_layout");

    string real_answer = result->real_answer;
    int i = 0;
    for (auto &option: result->options)
    {
        answerOptionList.append(new QCheckBox());
        answerOptionList.last()->setParent(MultipleChoiceFrame);
        string str = to_string(i) + ": " + option;
        answerOptionList.last()->setText(QString::fromStdString(str));
        MultipleChoiceLayout->addWidget(answerOptionList.last());

        // check the checkbox if the answer was correct.
        if (real_answer.find(to_string(i)) != string::npos)
            answerOptionList.last()->setChecked(true);

        // Instead of disabling it, we reset the state of the checkbox always, when it was
        // clicked, because if it is enabled, than the color of it changes.
        connect(answerOptionList.last(), SIGNAL(clicked()), this, SLOT(set_back_state()));
        i ++;
    }
}


void ResultDetailsWindow::set_back_state()
{
    QCheckBox *checkbox = qobject_cast<QCheckBox *>(sender());
    if (checkbox->isChecked()) checkbox->setChecked(false);
    else checkbox->setChecked(true);
}
