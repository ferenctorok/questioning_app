#include <utils.h>


QWidget* set_centralwidget(QMainWindow *parent,
                           const QString name)
{
    QWidget *centralwidget = new QWidget(parent);
    centralwidget->setObjectName(name);
    parent->setCentralWidget(centralwidget);
    return centralwidget;
}


QWidget* set_Qwidget(QWidget *parent,
                     const QString name,
                     QLayout *layout)
{
    QWidget *widget = new QWidget(parent);
    widget->setObjectName(name);
    if (layout != nullptr) layout->addWidget(widget);
    return widget;
}


QHBoxLayout* set_QHBoxLayout(QWidget *parent,
                             const QString name)
{
    QHBoxLayout *layout = new QHBoxLayout(parent);
    layout->setObjectName(name);
    return layout;
}


QVBoxLayout* set_QVBoxLayout(QWidget *parent,
                             const QString name)
{
    QVBoxLayout *layout = new QVBoxLayout(parent);
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
    if (layout != nullptr) layout->addWidget(button);
    return button;
}

QPushButton* set_QPushButton(const int max_width,
                             const int max_height,
                             QWidget *parent,
                             const QString name,
                             const QString text,
                             const QString tip_text,
                             QLayout *layout)
{
    QPushButton *button = set_QPushButton(parent, name, text, tip_text, layout);
    button->setMaximumSize(max_width, max_height);
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

QRadioButton* set_QRadioButton(QWidget *parent,
                               const QString name,
                               const QString text,
                               QLayout *layout)
{
    QRadioButton *button = new QRadioButton(parent);
    button->setObjectName(name);
    button->setText(text);
    if (layout != nullptr) layout->addWidget(button);
    return button;
}

QRadioButton* set_QRadioButton(const int max_width,
                               const int max_height,
                               QWidget *parent,
                               const QString name,
                               const QString text,
                               QLayout *layout)
{
    QRadioButton *button = set_QRadioButton(parent, name, text, layout);
    button->setMaximumSize(max_width, max_height);
    return button;
}


QTextEdit* set_QTextEdit(QWidget *parent,
                         const QString name,
                         const QString placeholder,
                         QLayout *layout)
{
    QTextEdit *textedit = new QTextEdit(parent);
    textedit->setObjectName(name);
    textedit->setPlaceholderText(placeholder);
    if (layout != nullptr) layout->addWidget(textedit);
    return textedit;
}

QTextEdit* set_QTextEdit(const int max_width,
                         const int max_height,
                         QWidget *parent,
                         const QString name,
                         const QString placeholder,
                         QLayout *layout)
{
    QTextEdit *textedit = set_QTextEdit(parent, name, placeholder, layout);
    textedit->setMaximumSize(max_width, max_height);
    return textedit;
}


QLabel* set_QLabel(QWidget* parent,
                   const QString text,
                   const QString name,
                   QLayout *layout)
{
    QLabel *label = new QLabel(text, parent);
    label->setObjectName(name);
    layout->addWidget(label);
    return label;
}

void add_option_to_list(QList<AnswerOption *> &list,
                     QWidget *parent,
                     const int num_of_rbs)
{
    for(int i = 0; i < num_of_rbs; i++)
    {
        list.append(new AnswerOption(parent));
    }
}


void add_OptionList_to_layout(const QList<AnswerOption *> &list,
                         QLayout *layout)
{
    for (const auto &widget : list)
    {
        layout->addWidget(widget);
    }
}








