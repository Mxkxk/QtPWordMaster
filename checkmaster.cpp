#include "checkmaster.h"

CheckMaster::CheckMaster(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Введіть мастер пароль");
    this->setFixedSize(300, 100);
    layout = new QVBoxLayout(this);

    line = new QLineEdit();
    button = new QPushButton("Підтвердити");

    layout->addWidget(line);
    layout->addWidget(button);

}
