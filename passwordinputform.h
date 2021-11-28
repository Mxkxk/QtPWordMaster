#ifndef PASSWORDINPUTFORM_H
#define PASSWORDINPUTFORM_H

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextEdit>

class PasswordInputForm : public QWidget
{
    Q_OBJECT

    QFormLayout *form;
    QLabel *pass_sourse, *pass_name, *pass_word, *comment_sourse;
    QLineEdit *source, *name, *password;
    QCheckBox *hide_pass;
    QTextEdit *comment;

public:
    explicit PasswordInputForm(QWidget *parent = nullptr);

signals:

};

#endif // PASSWORDINPUTFORM_H
