#include "passwordinputform.h"

PasswordInputForm::PasswordInputForm(QWidget *parent) : QWidget(parent)
{
    //
    form = new QFormLayout(this);    
    pass_sourse = new QLabel("Призначення паролю:");
    pass_name = new QLabel("Логін/Ім'я:");
    pass_word = new QLabel(" Пароль:");
    comment_sourse = new QLabel("Додатковий коментар:");

    source = new QLineEdit();
    name = new QLineEdit();
    password = new QLineEdit();

    hide_pass = new QCheckBox("Показати пароль");
    comment = new QTextEdit();
    comment->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    form->addRow(pass_sourse, source);
    form->addRow(pass_name, name);
    form->addRow(pass_word, password);
    form->addRow(new QWidget(), hide_pass);
    form->addRow(comment_sourse);
    form->addRow(comment);
    form->setMargin(0);

}
