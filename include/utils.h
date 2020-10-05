#ifndef UI_UTILS_H
#define UI_UTILS_H
#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QStatusBar>
#include <QRadioButton>
#include <QTextEdit>
#include <QList>

#include <answer_option.h>


QWidget* set_centralwidget(QMainWindow *parent = nullptr,
                           const QString name = "");

QWidget* set_Qwidget(QWidget *parent = nullptr,
                     const QString name = "",
                     QLayout *layout = nullptr);

QHBoxLayout* set_QHBoxLayout(QWidget *parent = nullptr,
                             const QString name = "");

QVBoxLayout* set_QVBoxLayout(QWidget *parent = nullptr,
                             const QString name = "");

QPushButton* set_QPushButton(QWidget *parent = nullptr,
                             const QString name = "",
                             const QString text = "",
                             const QString tip_text = "",
                             QLayout *layout = nullptr);

QPushButton* set_QPushButton(const int max_width,
                             const int max_height,
                             QWidget *parent = nullptr,
                             const QString name = "",
                             const QString text = "",
                             const QString tip_text = "",
                             QLayout *layout = nullptr);

QMenuBar* set_QMenuBar(QWidget *parent = nullptr,
                       const QString name = "");

QStatusBar* set_QStatusBar(QWidget *parent = nullptr,
                           const QString name = "");

QRadioButton* set_QRadioButton(QWidget *parent = nullptr,
                               const QString name = "",
                               const QString text = "",
                               QLayout *layout = nullptr);

QRadioButton* set_QRadioButton(const int max_width,
                               const int max_height,
                               QWidget *parent = nullptr,
                               const QString name = "",
                               const QString text = "",
                               QLayout *layout = nullptr);

QTextEdit* set_QTextEdit(QWidget *parent = nullptr,
                         const QString name = "",
                         const QString placeholder = "",
                         QLayout *layout = nullptr);

QTextEdit* set_QTextEdit(const int max_width,
                         const int max_height,
                         QWidget *parent = nullptr,
                         const QString name = "",
                         const QString placeholder = "",
                         QLayout *layout = nullptr);

void add_option_to_list(QList<AnswerOption *> &list,
                     QWidget *parent = nullptr,
                     const int num_of_rbs = 1);

void add_OptionList_to_layout(const QList<AnswerOption *> &list,
                         QLayout *layout);


#endif
