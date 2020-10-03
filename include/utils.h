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

QWidget* set_centralwidget(QMainWindow *parent = nullptr,
                           const QString name = "");

QHBoxLayout* set_QHBoxLayout(QWidget *parent = nullptr,
                             const QString name = "");

QPushButton* set_QPushButton(QWidget *parent = nullptr,
                             const QString name = "",
                             const QString text = "",
                             const QString tip_text = "",
                             QLayout *layout = nullptr);

QMenuBar* set_QMenuBar(QWidget *parent = nullptr,
                       const QString name = "");

QStatusBar* set_QStatusBar(QWidget *parent = nullptr,
                           const QString name = "");


#endif
