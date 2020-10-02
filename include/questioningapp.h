#ifndef QUESTIONINGAPP_H
#define QUESTIONINGAPP_H

#include <QMainWindow>

class QuestioningApp : public QMainWindow
{
    Q_OBJECT

public:
    QuestioningApp(QWidget *parent = nullptr);
    ~QuestioningApp();
};
#endif // QUESTIONINGAPP_H
