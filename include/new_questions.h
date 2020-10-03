#ifndef NEW_QUESTIONS_H
#define NEW_QUESTIONS_H
#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QList>
#include <QCloseEvent>


class NewQuestionsWindow: public QWidget
{
    Q_OBJECT
public:
    NewQuestionsWindow(QWidget *parent = nullptr);
    virtual ~NewQuestionsWindow();

public slots:

signals:
    void IsClosed();

private:
    void closeEvent(QCloseEvent *event);
    QWidget *centralwidget;
    QVBoxLayout *mainlayout;
    QHBoxLayout *QuestionTypeLayout;
    QRadioButton *multipleChoiceRB;
    QRadioButton *textAnswearRB;
    QVBoxLayout *MultipleChoiceLayout;
    QList<QRadioButton *> answear_rbutton_list;
};
#endif
