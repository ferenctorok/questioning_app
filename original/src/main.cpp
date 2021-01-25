#include <QApplication>
#include <questioningapp.h>
#include <QStyle>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuestioningApp w;
    w.show();
    return a.exec();
}
