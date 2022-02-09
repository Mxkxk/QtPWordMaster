#include "changemaster.h"

ChangeMaster::ChangeMaster(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Введіть новий мастер пароль");
    this->setFixedSize(300, 150);
    layout = new QVBoxLayout(this);

    lineold = new QLineEdit();
    lineold->setPlaceholderText("Старий мастер пароль");
    linenew = new QLineEdit();
    linenew->setPlaceholderText("Новий мастер пароль");

    button = new QPushButton("Підтвердити");

    layout->addWidget(lineold);
    layout->addWidget(linenew);
    layout->addWidget(button);
}
