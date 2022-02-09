#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pwordmaster.h"
#include "checkmaster.h"
#include "changemaster.h"
#include <QMainWindow>
#include <QScrollArea>
#include <QScrollBar>
#include <QMenu>
#include <QMenuBar>
#include <QFile>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QScrollArea *scroll_area;
    PWordMaster *pwordmaster;
    static const uint menusize = 4;
    QMenu *menu[menusize];
    QMenuBar *menubar;
    char key = 11;
    QString master = "master";
    QStringList pass;
    QFile *masterpass, *passwords;
    QAction *find_, *export_, *import_, *master_, *about_;
    CheckMaster *check;
    ChangeMaster *change;
    ulong initialised = 0;
    bool masterCheck = false;
public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void checkMaster();
    void changeMaster();
    void initialiseThis();
    char getKey();
signals:
    void initialise();
};

#endif // MAINWINDOW_H
