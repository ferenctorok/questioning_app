#ifndef QUESTIONINGAPP_H
#define QUESTIONINGAPP_H
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStatusBar>
#include <QMenuBar>

#include <new_questions.h>


class QuestioningApp : public QMainWindow
{
    Q_OBJECT

public:
    QuestioningApp(QWidget *parent = nullptr);
    virtual ~QuestioningApp() {};

protected slots:
    void button_new_questions_clicked();
    void button_start_clicked();
    void show_again();

protected:
    QWidget *centralwidget;
    QHBoxLayout *mainlayout;
    QPushButton *buttonNewQuestions;
    QPushButton *buttonStart;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    NewQuestionsWindow *new_questions_window;
};
#endif // QUESTIONINGAPP_H
