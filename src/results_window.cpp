#include <results.h>


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
    detail_window = nullptr;

    // setting icon:
    setWindowIcon(QIcon(":/img/question_mark.ico"));

    // setting up the widget (window)
    setAttribute(Qt::WA_DeleteOnClose);
    resize(600, 400);
    setObjectName("results_window");
    setWindowTitle("Eredmények");

    // main layout of the window
    mainLayout = set_QVBoxLayout(this, "main_layout");

    // main info layout:
    mainInfoLayout = set_QHBoxLayout(nullptr, "main_info_layout");
    mainLayout->addLayout(mainInfoLayout);

    // main info label:
    string main_info_string = getMainInfoString();
    mainInfoLabel = set_QLabel(this, QString::fromStdString(main_info_string),
                               "main_info_label", mainInfoLayout);

    // smiley label:
    smileyLabel = set_QLabel(this, "", "smiley_label", mainInfoLayout);
    //smileyLabel->setPixmap(QString("/home/ferenc/Documents/programming/questioning_app/src/img/smiley_best.png"));

    // scroll area:
    scrollArea = new QScrollArea(this);
    scrollArea->setObjectName("scrollArea");
    scrollArea->setWidgetResizable(true);

    ScrollAreaWidget = new QWidget();
    ScrollAreaWidgetLayout = set_QVBoxLayout(ScrollAreaWidget);

    // setting up palettes:
    correctPaletteFirst = new QPalette(Qt::green);
    correctPalette = new QPalette(Qt::yellow);
    wrongPalette = new QPalette(Qt::red);


    // Lists:
    widgetList = new QList<QWidget *>;
    buttonList = new QList<QPushButton *>;
    labelList = new QList<QLabel *>;
    layoutList = new QList<QHBoxLayout *>;

    // setting up the list of results:
    for (auto &result: *results) set_up_lists(result);

    scrollArea->setWidget(ScrollAreaWidget);
    mainLayout->addWidget(scrollArea);
}


ResultsWindow::~ResultsWindow() {delete results;}


void ResultsWindow::closeEvent(QCloseEvent *event)
{
    emit IsClosed();
    QWidget::closeEvent(event);
}


void ResultsWindow::set_up_lists(Result *result)
{
    // setting up the label with background color:
    QWidget *widget = new QWidget(ScrollAreaWidget);
    widget->setAutoFillBackground(true);
    if (result->correct)
        if (stoi(result->trials) == 1) widget->setPalette(*correctPaletteFirst);
        else widget->setPalette(*correctPalette);
    else widget->setPalette(*wrongPalette);
    widgetList->append(widget);

    // horizontal layout for each widget:
    layoutList->append(new QHBoxLayout(widget));

    // setting up the text to be displayed and the label:
    string text = "";
    text += "Feladat " + result->question_number + " : ";
    if (result->correct)
        if (stoi(result->trials) == 1) text += "JÓ\n";
        else text += "JÓ, de nem elsőre\n";
    else text += "ROSSZ\n";
    text += "próbálkozások száma: " + result ->trials;
    QLabel *label = set_QLabel(800, widget, QString::fromStdString(text),
                               "", layoutList->last());
    labelList->append(label);

    // setting up the details button:
    QPushButton *button = set_QPushButton(150, 60, widget, "",
                                          "részletek", "A feladat részleteinek megjelenítése",
                                          layoutList->last());
    connect(button, SIGNAL(clicked()), this, SLOT(details_button_clicked()));
    buttonList->append(button);

    // adding the new widget to the scrollable layout.
    ScrollAreaWidgetLayout->addWidget(widget);
}


void ResultsWindow::details_button_clicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    int index = buttonList->indexOf(button);
    detail_window = new ResultDetailsWindow(results->at(index));
    detail_window->show();
}


string ResultsWindow::getMainInfoString()
{
    string str = "";

    int num_of_questions = results->size();
    int num_correct_answers = getNumOfCorrectAnswers();
    int num_correct_answers_first = getNumOfCorrectAnswersFirst();

    double ratio = (double)num_correct_answers_first / (double)num_of_questions;
    if (ratio >= 0.7) str += "Gratulálok! Büszke lehetsz a tudásodra!\n\n";
    else if (ratio >= 0.4) str += "Sok mindent tudtál, de még van mit megtanulnod.\n\n";
    else str += "Kapcsolj rá, mert a tudásod nagyon bizonytalan!\n\n";

    str += "Összesen feltett kérdések száma: " + to_string(num_of_questions) + "\n";
    str += "Helyesen megválaszolt kérdések száma: " + to_string(num_correct_answers) + "\n";
    str += "Elsőre helyesen megválaszolt kérdések száma: " + to_string(getNumOfCorrectAnswersFirst());

    return str;
}


int ResultsWindow::getNumOfCorrectAnswers()
{
    int counter = 0;
    for (auto &result: *results)
        if (result->correct) counter ++;
    return counter;
}


int ResultsWindow::getNumOfCorrectAnswersFirst()
{
    int counter = 0;
    for (auto &result: *results)
        if (result->correct && (stoi(result->trials) == 1))
            counter ++;
    return counter;
}





