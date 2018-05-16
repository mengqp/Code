#include "ctab.h"


CTab::CTab(QMainWindow *parent)
{
    if(0 == parent)
    {
        return;
    }
    m_mainWindow = parent;
    InitUI();
}

CTab::~CTab()
{



    delete m_tabData;



}

void CTab::InitUI()
{
    m_tabData = new QTabWidget(m_mainWindow);
    m_mainWindow->setCentralWidget(m_tabData);

}
