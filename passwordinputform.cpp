#include "passwordinputform.h"
#include <QRegExp>

PasswordInputForm::PasswordInputForm(QWidget *parent) : QWidget(parent)
{
    //
    form = new QFormLayout(this);    
    pass_sourse = new QLabel("Призначення паролю:");
    pass_name = new QLabel("Логін/Ім'я:");
    pass_word = new QLabel(" Пароль:");

    source = new QLineEdit();
    name = new QLineEdit();
    password = new QLineEdit();
    password->setEchoMode(QLineEdit::Password);

    delete_pass = new QPushButton("Видалити");

    hide_pass = new QCheckBox("Показати пароль");    

    form->addRow(pass_sourse, source);
    form->addRow(pass_name, name);
    form->addRow(pass_word, password);
    form->addRow(delete_pass, hide_pass);
    form->setMargin(0);

    connect(hide_pass, SIGNAL(clicked()), this, SLOT(showPassword()));
}

void PasswordInputForm::setPos(uint pos)
{
    position = pos;
    delete_pass->setObjectName(QString("%1").arg(position));
}

QString* PasswordInputForm::toString()
{
    QString *str = new QString[3];    
    str[0] = source->text();
    str[1] = name->text();
    str[2] = password->text();
    return str;
}

void PasswordInputForm::setLines(QString src, QString nm, QString pswrd)
{
    source->setText(src);
    name->setText(nm);
    password->setText(pswrd);
}

void PasswordInputForm::validateForm()
{
    QRegExp reg("( *[^ ]+ *)+");
    if(reg.indexIn(source->text()) != -1 || reg.indexIn(name->text()) != -1)
    {
        if(password->text().length() > 1)
        {
            isValid = true;
            qDebug(qPrintable(QString("Form %1 is valid : %2").arg(position).arg(isValid)));
            emit validated(position, toString());
        }
    }
}

void PasswordInputForm::showPassword()
{
    if(hide_pass->isChecked())password->setEchoMode(QLineEdit::Normal);
    else password->setEchoMode(QLineEdit::Password);
}
