#ifndef NEW_QUESTIONS_H
#define NEW_QUESTIONS_H
#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QList>
#include <QCloseEvent>
#include <QTextEdit>


class NewQuestionsWindow: public QWidget
{
    Q_OBJECT
public:
    NewQuestionsWindow(QWidget *parent = nullptr);
    virtual ~NewQuestionsWindow();

public slots:
    void multiChRB_clicked();
    void textAnsRb_clicked();
signals:
    void IsClosed();

private:
    QVBoxLayout *mainlayout;
    QHBoxLayout *questionTypeLayout;
    QRadioButton *multipleChoiceRB;
    QRadioButton *textAnswerRB;
    QTextEdit *QuestionTextEdit;
    QTextEdit *AnswerTextEdit;
    QWidget *MultipleChoiceWidget;
    QVBoxLayout *MultipleChoiceLayout;
    QList<QRadioButton *> answearRBlist;

    void closeEvent(QCloseEvent *event);
};
#endif
