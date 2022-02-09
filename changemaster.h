#ifndef CHANGEMASTER_H
#define CHANGEMASTER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class ChangeMaster : public QWidget
{
    Q_OBJECT

    QVBoxLayout *layout;

public:
    explicit ChangeMaster(QWidget *parent = nullptr);
    QLineEdit *lineold, *linenew;
    QPushButton *button;

signals:

};

#endif // CHANGEMASTER_H
