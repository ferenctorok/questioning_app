#ifndef NEW_QUESTIONS_H
#define NEW_QUESTIONS_H
#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QList>


class NewQuestionsWindow: public QDialog
{
    Q_OBJECT
public:
    NewQuestionsWindow(QWidget *parent = nullptr);
    virtual ~NewQuestionsWindow();

public slots:
    //bool close();
    void reject();

signals:
    void IsClosed();

private:
    QWidget *centralwidget;
    QVBoxLayout *mainlayout;
    QHBoxLayout *QuestionTypeLayout;
    QRadioButton *multipleChoiceRB;
    QRadioButton *textAnswearRB;
    QVBoxLayout *MultipleChoiceLayout;
    QList<QRadioButton *> answear_rbutton_list;
};
#endif
