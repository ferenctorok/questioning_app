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

    // setting up palettes:
    correctPalette = new QPalette(Qt::green);
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
    if (result->correct) widget->setPalette(*correctPalette);
    else widget->setPalette(*wrongPalette);
    widgetList->append(widget);

    // horizontal layout for each widget:
    layoutList->append(new QHBoxLayout(widget));

    // setting up the text to be displayed and the label:
    string text = "";
    text += "Feladat " + result->question_number + " : ";
    if (result->correct) text += "JÓ\n";
    else text += "ROSSZ\n";
    text += "próbálkozások száma: " + result ->trials;
    QLabel *label = set_QLabel(widget, QString::fromStdString(text),
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





