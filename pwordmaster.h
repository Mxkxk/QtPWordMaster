#ifndef PWORDMASTER_H
#define PWORDMASTER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QList>
#include <passwordinputform.h>

class PWordMaster : public QWidget
{
    Q_OBJECT
    QVBoxLayout *v_layout;
    QHBoxLayout *h_layout;   
    QList<PasswordInputForm*> buttons;
    QPushButton *add, *remove;
    QWidget *add_remove;

public:
    PWordMaster(QWidget *parent = nullptr);
public slots:
    void changeLayout();


};

#endif // PWORDMASTER_H
