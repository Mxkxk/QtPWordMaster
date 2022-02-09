#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->show();
    this->resize(600, 480);
    this->setMinimumSize(400, 300);
    ///
    /// masterpass check
    masterpass = new QFile(".masterpass");
    masterpass->open(QIODevice::ReadWrite);
    //
    if(masterpass->isOpen())
    {        
        qDebug(qPrintable(master));
        //
        auto masterbuff = masterpass->readLine();
        QByteArray masterbyte;
        for(int i = 0; i < masterbuff.length(); i++)masterbyte.append(masterbuff.at(i)^key);
        master = QString(masterbyte);
        //
        qDebug(qPrintable("masterpass/"+master));
        masterbyte.clear();
        if(master.length() < 6)
        {
            qDebug(qPrintable("MasterPassError\nMasterPass is default"));
            //
            master = "master";
            masterbuff = master.toUtf8();
            for(int i = 0; i < masterbuff.length(); i++)masterbyte.append(masterbuff.at(i)^key);
            masterpass->write(masterbyte);
            //check
            masterbuff = masterpass->readLine();
            masterbyte.clear();
            for(int i = 0; i < masterbuff.length(); i++)masterbyte.append(masterbuff.at(i)^key);
            auto __check_master = QString(masterbyte);
            //
            qDebug(qPrintable(master+"|"+__check_master));
        }
    }
    else qDebug(qPrintable("MasterPassError"));
    masterpass->close();

    ///passwords check
    ///
    passwords = new QFile(".passwords");
    passwords->open(QIODevice::ReadWrite);
    if(passwords->isOpen())
    {
        //
        auto passwordbuff = passwords->readAll();
        for(int i = 0; i < passwordbuff.length(); i++)passwordbuff[i] = passwordbuff[i] ^ key;
        qDebug(qPrintable(QString("%1").arg(passwordbuff.length())));
        qDebug(qPrintable(QString(passwordbuff)));
        pass = QString(passwordbuff).split('\n');
    }
    else qDebug(qPrintable("PasswordsError"));
    passwords->close();

    check = new CheckMaster();    
    check->show();

    change = new ChangeMaster();

    connect(check->button, SIGNAL(clicked()), this, SLOT(checkMaster()));
    connect(change->button, SIGNAL(clicked()), this, SLOT(changeMaster()));
    connect(this, SIGNAL(initialise()), this, SLOT(initialiseThis()));

}

void MainWindow::checkMaster()
{
    if(check->isHidden())
    {
        check->line->setText("");
        check->show();
    }
    else
    {
        check->hide();
        if(check->line->text() == master)
        {
            masterCheck = true;
            initialised++;
            if(initialised != 0)emit initialise();
        }
        else
        {
            masterCheck = false;
            if(initialised == 0)this->close();
        }
        qDebug(qPrintable(QString("Master check: %1").arg(masterCheck)));
    }
}

void MainWindow::changeMaster()
{
    if(change->isHidden())
    {
        change->lineold->setText("");
        change->linenew->setText("");
        change->show();
    }
    else
    {
        change->hide();
        if(change->lineold->text() == master)
        {
            masterCheck = true;
            if(change->lineold->text().length() >= 6)
            {
                master = change->linenew->text();
                qDebug(qPrintable("-------------------------------------"));

                masterpass = new QFile(".masterpass");
                masterpass->open(QIODevice::ReadWrite);
                //
                if(masterpass->isOpen())
                {
                    masterpass->resize(0);
                    qDebug(qPrintable(master));
                    //
                    auto masterbuff = master.toUtf8();
                    QByteArray masterbyte;
                    for(int i = 0; i < masterbuff.length(); i++)masterbyte.append(masterbuff.at(i)^key);
                    masterpass->write(masterbyte);
                    //
                }
                masterpass->close();
            }
        }
        else masterCheck = false;
        qDebug(qPrintable(QString("Master check: %1").arg(masterCheck)));
    }
}

void MainWindow::initialiseThis()
{
    ///
    ///pwordmaster and scrollarea creation
    pwordmaster = new PWordMaster();    
    ///
    ///menu creation
    menu[0] = new QMenu("Паролі");
    menu[0]->addAction("Зберегти паролі", pwordmaster, SLOT(save_()));
    menu[1] = new QMenu("Пошук паролів");
    find_ = menu[1]->addAction("Увести фільтр", pwordmaster, SLOT(filter_()));
    menu[2] = new QMenu("Експорт/імпорт");
    export_ = menu[2]->addAction("Експорт паролів", pwordmaster, SLOT(export_()));
    import_ = menu[2]->addAction("Імпорт паролів", pwordmaster, SLOT(import_()));
    menu[3] = new QMenu("Про програму");
    master_ = menu[3]->addAction("&Зміна мастер пароля", this, SLOT(changeMaster()));    

    menubar = new QMenuBar();

    for(int i = 0; i < menusize; i++)menubar->addMenu(menu[i]);

    this->setMenuWidget(menubar);


    //
    scroll_area = new QScrollArea;
    scroll_area->resize(this->size());
    scroll_area->setWidgetResizable(true);
    scroll_area->setWidget(pwordmaster);
    pwordmaster->import_(pass);
    //
    this->setCentralWidget(scroll_area);


    ///

}

char MainWindow::getKey()
{
    return key;
}
