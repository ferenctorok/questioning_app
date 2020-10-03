#include <utils.h>


QWidget* set_centralwidget(QMainWindow *parent,
                           const QString name)
{
    QWidget *centralwidget = new QWidget(parent);
    centralwidget->setObjectName(name);
    parent->setCentralWidget(centralwidget);
    return centralwidget;
}


QHBoxLayout* set_QHBoxLayout(QWidget *parent,
                             const QString name)
{
    QHBoxLayout *layout = new QHBoxLayout(parent);
    layout->setObjectName(name);
    return layout;
}


QPushButton* set_QPushButton(QWidget *parent,
                             const QString name,
                             const QString text,
                             const QString tip_text,
                             QLayout *layout)
{
    QPushButton *button = new QPushButton(parent);
    button->setObjectName(name);
    button->setText(text);
    button->setToolTip(tip_text);
    layout->addWidget(button);
    return button;
}


QMenuBar* set_QMenuBar(QWidget *parent,
                       const QString name)
{
    QMenuBar *menubar = new QMenuBar(parent);
    menubar->setObjectName(name);
    menubar->setGeometry(QRect(0, 0, 800, 22));
    return menubar;
}


QStatusBar* set_QStatusBar(QWidget *parent,
                       const QString name)
{
    QStatusBar *statusbar = new QStatusBar(parent);
    statusbar->setObjectName(name);
    return statusbar;
}








