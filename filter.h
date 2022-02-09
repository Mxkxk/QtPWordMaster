#ifndef FILTER_H
#define FILTER_H

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class Filter : public QWidget
{
    Q_OBJECT

    QVBoxLayout *layout;

public:
    explicit Filter(QWidget *parent = nullptr);

    QLineEdit *line;
    QPushButton *button;

signals:

};

#endif // FILTER_H
