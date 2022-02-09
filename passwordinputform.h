#ifndef PASSWORDINPUTFORM_H
#define PASSWORDINPUTFORM_H

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextEdit>
#include <QPushButton>

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
    void setPos(uint pos);
    QString* toString();
    void setLines(QString src, QString nm, QString pswrd);

    QPushButton *delete_pass;
    bool isValid = false;
    uint position;    

public slots:
    void validateForm();
    void showPassword();

signals:
    void validated(uint pos, QString* str);

};

#endif // PASSWORDINPUTFORM_H
