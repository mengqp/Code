#ifndef CCOMM_H
#define CCOMM_H

#include <QMenu>
class pdtwindow;

class ccomm
{
public:
    explicit ccomm( pdtwindow *parent);
    ~ccomm();

private:
    //定义主窗口
    pdtwindow *m_mainWindow;

    QMenu *m_menu;

};

#endif // CCOMM_H
