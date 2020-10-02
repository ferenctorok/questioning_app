#ifndef QUESTIONINGAPP_H
#define QUESTIONINGAPP_H

#include <QMainWindow>
#include <QPushButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>


class QuestioningApp : public QMainWindow
{
    Q_OBJECT

public:
    QuestioningApp(QWidget *parent = nullptr);
    ~QuestioningApp();

protected:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;
};
#endif // QUESTIONINGAPP_H
