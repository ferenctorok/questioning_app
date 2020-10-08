#ifndef QUESTIONINGAPP_H
#define QUESTIONINGAPP_H
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStatusBar>
#include <QMenuBar>
#include <QMessageBox>

#include <new_questions.h>
#include <question_utils.h>


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

    vector<Question *>* readQuestions(string filename);
    vector<Question *>* question_file_corrupted(const string &error_msg = "");
    string get_text_after(ifstream &infile,
                          streampos &oldpos,
                          string &error_msg,
                          const string after_this = "");
    vector<int> get_multi_answers_from_string(string str);


};
#endif // QUESTIONINGAPP_H
