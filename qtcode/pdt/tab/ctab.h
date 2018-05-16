#ifndef CTAB_H
#define CTAB_H

#include <QMainWindow>
#include <QTabWidget>



class CTab
{
public:
    CTab(QMainWindow *parent = 0);
    ~CTab();
public:
     void InitUI();

public:
    QTabWidget *m_tabData;
private:
    //定义主窗口
    QMainWindow *m_mainWindow;

};

#endif // CDATATAB_H
