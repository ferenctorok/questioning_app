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
#include <QLabel>
#include <QSpinBox>
#include <QFrame>

#include <answer_option.h>
#include <fstream>
#include <iostream>

using namespace std;


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

QLabel* set_QLabel(QWidget* parent = nullptr,
                   const QString text = "",
                   const QString name = "",
                   QLayout *layout = nullptr);

QLabel* set_QLabel(int max_width,
                   QWidget* parent = nullptr,
                   const QString text = "",
                   const QString name = "",
                   QLayout *layout = nullptr);

QSpinBox* set_QSpinBox(QWidget* parent = nullptr,
                       const QString name = "",
                       QLayout *layout = nullptr);

QFrame* set_QFrame(QWidget* parent = nullptr,
                   const QString name = "",
                   QLayout *layout = nullptr);

void add_option_to_list(QList<AnswerOption *> &list,
                     QWidget *parent = nullptr,
                     const int num_of_rbs = 1);

void add_OptionList_to_layout(const QList<AnswerOption *> &list,
                         QLayout *layout);

vector<int> get_multi_answers_from_string(string str);

void write_section(ofstream &outfile,
                   string header,
                   string content);

vector<string> vectorize_string(string options_string);

string read_section(ifstream &infile,
                    streampos &oldpos,
                    const string header,
                    const string section_marker,
                    string &error_msg);

#endif
