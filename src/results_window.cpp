#include <results_window.h>


Result::Result(string question_number,
               bool correct,
               string trials,
               string type,
               string question,
               string real_answer,
               vector<string> options,
               vector<string> given_answers)
{
    this->question_number = question_number;
    this->correct = correct;
    this->trials = trials;
    this->type = type;
    this->question = question;
    this->real_answer = real_answer;
    this->options = options;
    this->given_answers = given_answers;
}


ResultsWindow::ResultsWindow(vector<Result *> *results,
                             QWidget *parent):
    QWidget(parent)
{
    this->results = results;

    // setting up the widget (window)
    setAttribute(Qt::WA_DeleteOnClose);
    resize(600, 400);
    setObjectName("results_window");
    setWindowTitle("Eredmények megjelenítése");

    // main layout of the window
    mainLayout = set_QHBoxLayout(this, "main_layout");

    // scroll area:
    scrollArea = new QScrollArea(this);
    scrollArea->setObjectName("scrollArea");
    scrollArea->setWidgetResizable(true);

    ScrollAreaWidget = new QWidget();
    ScrollAreaWidgetLayout = set_QVBoxLayout(ScrollAreaWidget);

    // List of buttons:
    buttonList = new QList<QPushButton *>;
    for (int i = 0; i < 10; i++)
    {
        buttonList->append(new QPushButton(ScrollAreaWidget));
        ScrollAreaWidgetLayout->addWidget(buttonList->last());
    }

    scrollArea->setWidget(ScrollAreaWidget);
    mainLayout->addWidget(scrollArea);
}


ResultsWindow::~ResultsWindow() {delete results;}


void ResultsWindow::closeEvent(QCloseEvent *event)
{
    emit IsClosed();
    QWidget::closeEvent(event);
}





