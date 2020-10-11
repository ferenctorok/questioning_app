#include <results.h>


ResultDetailsWindow::ResultDetailsWindow(Result *result,
                                         QWidget *parent):
    QWidget(parent)
{
    this->result = result;
    // setting up the widget (window)
    setAttribute(Qt::WA_DeleteOnClose);
    resize(400, 300);
    setObjectName("result_detail_window");
    string title = "Feladat " + result->question_number;
    setWindowTitle(QString::fromStdString(title));
}


ResultDetailsWindow::~ResultDetailsWindow() {delete result;}
