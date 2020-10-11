#include <results.h>


ResultDetailsWindow::ResultDetailsWindow(Result *result,
                                         QWidget *parent):
    QWidget(parent)
{
    this->result = result;
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

    }

    // given answers:
    GivenAnswersLabel = set_QLabel(550, this, "", "given_answers_label", mainlayout);
    string given_answers = "Adott válaszok:\n";
    for (auto &answer: result->given_answers)
        given_answers += "\t" + answer + "\n";
    GivenAnswersLabel->setText(QString::fromStdString(given_answers));
}


ResultDetailsWindow::~ResultDetailsWindow() {delete result;}
