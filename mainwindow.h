#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pwordmaster.h"
#include <QMainWindow>
#include <QScrollArea>
#include <QScrollBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QScrollArea *scroll_area;
    PWordMaster *pwordmaster;

public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

};

#endif // MAINWINDOW_H
