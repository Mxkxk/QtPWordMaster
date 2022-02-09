#include "pwordmaster.h"

#include <QMessageBox>

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

    filter = new Filter();

    connect(filter->button, SIGNAL(clicked()), this, SLOT(filter_()));
    connect(add, SIGNAL(clicked()), this, SLOT(changeLayout()));
    connect(remove, SIGNAL(clicked()), this, SLOT(changeLayout()));
}

void PWordMaster::changeLayout()
{
    if(sender()->objectName() == "add")
    {
        if(buttons.length() == 0)
        {
            buttons.push_back(new PasswordInputForm());
            v_layout->insertWidget(v_layout->count()-1, buttons.value(v_layout->count()-1));
            connect(buttons.last()->delete_pass, SIGNAL(clicked()), this, SLOT(deletePass()));
        }
        else
        {
            buttons.last()->validateForm();
            if(buttons.last()->isValid)
            {
                buttons.push_back(new PasswordInputForm());
                v_layout->insertWidget(v_layout->count()-1, buttons.value(v_layout->count()-1));
                connect(buttons.last()->delete_pass, SIGNAL(clicked()), this, SLOT(deletePass()));
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setText("Інформація не валідна, заповніть поля і/або додайте пароль");
                msgBox.exec();
            }
        }
    }
    else if(sender()->objectName() == "remove")
    {
        v_layout->removeWidget(buttons.value(v_layout->count()-1));
        disconnect(buttons.last()->delete_pass, SIGNAL(clicked()), this, SLOT(deletePass()));
        delete buttons.value(buttons.count()-1);        
        buttons.removeAt(buttons.count()-1);
    }    
    if(buttons.count() == 0)remove->setEnabled(false);
    else remove->setEnabled(true);

    updatePos();
}

void PWordMaster::updatePos()
{
    for(int i = 0; i < buttons.length(); i++)buttons.at(i)->setPos(i);
}

void PWordMaster::filter_()
{
    if(filter->isHidden())
    {
        filter->line->setText("");
        filter->show();
    }
    else {
        filter->hide();
        filter_(filter->line->text());
    }
}

void PWordMaster::filter_(QString fltr)
{
    //
    filtered = new PWordMaster;    

    if(fltr.length() > 0)
    {
        QList<PasswordInputForm*> buttons_filtered;

        for(int i = 0; i < buttons.count(); i++ )
            if(buttons.at(i)->toString()[0].contains(fltr, Qt::CaseSensitivity::CaseInsensitive) || buttons.at(i)->toString()[1].contains(fltr, Qt::CaseSensitivity::CaseInsensitive))
            {
                buttons_filtered.append(new PasswordInputForm);
                auto str = buttons.at(i)->toString();
                buttons_filtered.last()->setLines(str[0], str[1], str[2]);
                buttons_filtered.last()->delete_pass->setEnabled(false);
            }

        filtered->import_(buttons_filtered);
        filtered->show();
    }
}

void PWordMaster::clearFilter()
{
    filter_("");
}

void PWordMaster::export_()
{
    auto file = QFileDialog::getSaveFileName(this, "Експорт паролів", "passwords.txt");
    qDebug(qPrintable(file));
    QFile exportPass(file);
    exportPass.open(QIODevice::WriteOnly);
    if(exportPass.isOpen())
    {
        exportPass.resize(0);
        for(int i = 0; i < buttons.size(); i++)
        {
            buttons.at(i)->validateForm();
            if(buttons.at(i)->isValid)
                for(int j = 0; j < 3; j++)
                {
                    if(buttons.at(i)->toString()[j][buttons.at(i)->toString()[j].length()-1]!='\n')exportPass.write((buttons.at(i)->toString()[j]+"\n").toUtf8());
                    else exportPass.write((buttons.at(i)->toString()[j]).toUtf8());
                }
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Неправильний шлях!!!");
        msgBox.exec();
    }
    exportPass.close();
}

void PWordMaster::import_()
{
    auto file = QFileDialog::getOpenFileName(this, "Імпорт паролів");
    QFile importPass(file);
    importPass.open(QIODevice::ReadOnly);
    if(importPass.isOpen())
    {
        qDebug(qPrintable("1"));
        QList<QByteArray> imported;
        QTextStream importStream(&importPass);
        while(!importStream.atEnd())
            imported.append(importPass.readLine());
        if(imported.size()%3 == 0 && imported.size() > 0)
        {
            for(int i = 0; i < imported.size()/3; i++)
            {
                buttons.push_back(new PasswordInputForm());
                v_layout->insertWidget(v_layout->count()-1, buttons.value(v_layout->count()-1));
                connect(buttons.last()->delete_pass, SIGNAL(clicked()), this, SLOT(deletePass()));
                buttons.last()->setLines(QString(imported.at(i*3)), QString(imported.at(i*3+1)), QString(imported.at(i*3+2)));
                updatePos();
            }
            remove->setEnabled(true);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Неправильна кількість рядків!!!");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Неправильний шлях!!!");
        msgBox.exec();
    }
    importPass.close();
}

void PWordMaster::import_(QStringList str)
{
    qDebug(qPrintable(QString("%1").arg(str.length())));
    if((str.length()%3 == 0 || str.length()%3 == 1) && str.length() > 0)
    {
        for(int i = 0; i < str.length()/3; i++)
        {
            buttons.push_back(new PasswordInputForm());
            v_layout->insertWidget(v_layout->count()-1, buttons.value(v_layout->count()-1));
            connect(buttons.last()->delete_pass, SIGNAL(clicked()), this, SLOT(deletePass()));
            buttons.last()->setLines(str.at(i*3), str.at(i*3+1), str.at(i*3+2));
            updatePos();
        }
        remove->setEnabled(true);
    }
    else qDebug(qPrintable("PasswordsLoadingError"));
}

void PWordMaster::import_(QList<PasswordInputForm *> b)
{
    v_layout->removeWidget(add_remove);
    delete add_remove;
    //v_layout = new QVBoxLayout(this);
    //v_layout->setAlignment(Qt::AlignTop);

    for(int i = 0; i < b.count(); i++)
    {
        b.at(i)->delete_pass->setEnabled(false);
        v_layout->addWidget(b.at(i));
    }

}

void PWordMaster::deletePass()
{
    auto position = ((PasswordInputForm*)(sender()->parent()))->position;
    v_layout->removeWidget(buttons.value(position));
    disconnect(buttons.at(position)->delete_pass, SIGNAL(clicked()), this, SLOT(deletePass()));
    delete buttons.value(position);
    buttons.removeAt(position);
    ///
    updatePos();
}

void PWordMaster::save_()
{
    QFile savePass(".passwords");
    savePass.open(QIODevice::WriteOnly);
    if(savePass.isOpen())
    {
        savePass.resize(0);
        for(int i = 0; i < buttons.size(); i++)
        {
            buttons.at(i)->validateForm();
            if(buttons.at(i)->isValid)
                for(int j = 0; j < 3; j++)
                {
                    if(buttons.at(i)->toString()[j][buttons.at(i)->toString()[j].length()-1]!='\n')
                    {
                        auto buff = (buttons.at(i)->toString()[j]+"\n").toUtf8();
                        for(int k = 0; k < buff.count(); k++)
                        {
                            buff[k] = buff[k]^11;
                            //qDebug(qPrintable(QString(((MainWindow*)(this->parent()->parent()))->getKey())));
                        }
                        savePass.write(buff);
                    }
                    else
                    {
                        auto buff = (buttons.at(i)->toString()[j]).toUtf8();
                        for(int k = 0; k < buff.count(); k++)
                        {
                            buff[k] = buff[k]^11;
                        }
                        savePass.write(buff);
                    }
                }
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Невдалося записати файл((");
        msgBox.exec();
    }
}

