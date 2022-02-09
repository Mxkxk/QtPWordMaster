#ifndef CHECKMASTER_H
#define CHECKMASTER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class CheckMaster : public QWidget
{
    Q_OBJECT

    QVBoxLayout *layout;

public:
    explicit CheckMaster(QWidget *parent = nullptr);
    QLineEdit *line;
    QPushButton *button;

signals:

};

#endif // CHECKMASTER_H
