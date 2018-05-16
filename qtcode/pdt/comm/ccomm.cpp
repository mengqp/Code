#include "ccomm.h"
#include "../pdtwindow.h"

ccomm::ccomm( pdtwindow *parent)
{
    if(0 == parent)
    {
        return;
    }
    m_mainWindow = (pdtwindow *)parent;

    m_menu = new QMenu(FROMLOCAL("类型"), m_mainWindow);

    m_mainWindow->m_menu[2]->insertMenu(m_mainWindow->m_action[2][0],m_menu);
    m_menu->addAction( m_mainWindow->m_action[0][2]);
    m_menu->addAction( m_mainWindow->m_action[0][0]);
    m_menu->addAction( m_mainWindow->m_action[0][1]);




}

ccomm::~ccomm()
{

}

