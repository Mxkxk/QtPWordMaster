#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->resize(600, 480);
    scroll_area = new QScrollArea;
    scroll_area->resize(this->size());
    scroll_area->setWidgetResizable(true);
    pwordmaster = new PWordMaster();
    scroll_area->setWidget(pwordmaster);
    this->setCentralWidget(scroll_area);
}
