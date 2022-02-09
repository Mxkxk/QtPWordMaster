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
#include <QFileDialog>
#include <QTextStream>
#include <filter.h>

class PWordMaster : public QWidget
{
    Q_OBJECT
    QVBoxLayout *v_layout;
    QHBoxLayout *h_layout;   
    QList<PasswordInputForm*> buttons;
    QPushButton *add, *remove;
    QWidget *add_remove;
    Filter *filter;
    PWordMaster *filtered;

public:
    PWordMaster(QWidget *parent = nullptr);

public slots:
    void changeLayout();
    void updatePos();
    void filter_();
    void filter_(QString fltr);
    void clearFilter();
    void export_();
    void import_();
    void import_(QStringList str);
    void import_(QList<PasswordInputForm*> b);
    void deletePass();
    void save_();
};

#endif // PWORDMASTER_H
