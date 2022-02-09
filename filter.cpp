#include "filter.h"

Filter::Filter(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Введіть фільтр");
    this->setFixedSize(300, 100);
    layout = new QVBoxLayout(this);

    line = new QLineEdit();
    button = new QPushButton("Підтвердити");

    layout->addWidget(line);
    layout->addWidget(button);
}
