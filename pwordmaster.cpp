#include "pwordmaster.h"

PWordMaster::PWordMaster(QWidget *parent) : QWidget(parent)
{
    this->show();

    v_layout = new QVBoxLayout(this);
    v_layout->setAlignment(Qt::AlignTop);    

    add = new QPushButton("+");
    add->setObjectName("add");

    remove = new QPushButton("-");
    remove->setObjectName("remove");
    remove->setEnabled(false);

    add_remove = new QWidget();
    h_layout = new QHBoxLayout(add_remove);
    h_layout->addWidget(add);
    h_layout->addWidget(remove);
    h_layout->setContentsMargins(0, 0, 0, 0);

    v_layout->addWidget(add_remove);
    connect(add, SIGNAL(clicked()), this, SLOT(changeLayout()));
    connect(remove, SIGNAL(clicked()), this, SLOT(changeLayout()));
}

void PWordMaster::changeLayout()
{
    if(sender()->objectName() == "add")
    {
        buttons.push_back(new PasswordInputForm());
        v_layout->insertWidget(v_layout->count()-1, buttons.value(v_layout->count()-1));
    }else if(sender()->objectName() == "remove")
    {
        v_layout->removeWidget(buttons.value(v_layout->count()-1));
        delete buttons.value(buttons.count()-1);
        buttons.removeAt(buttons.count()-1);
    }
    if(buttons.count() == 0)remove->setEnabled(false);
    else remove->setEnabled(true);
}

