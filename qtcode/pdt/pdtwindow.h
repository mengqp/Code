#ifndef PDTWINDOW_H
#define PDTWINDOW_H

#include <QMainWindow>
#include	<QStatusBar>
#include	<QAction>
#include	<QMenuBar>
#include	<QMenu>
#include	<QIcon>
#include    <QToolBar>

#include	"./public/datatype.h"
#include	"./public/cxml.h"

#include	"./project/cprjnew.h"
#include	"./project/cprjopen.h"

#include    "./dock/cdock.h"
#include    "./tab/ctab.h"
#include    "./comm/ccomm.h"

class pdtwindow : public QMainWindow
{
    Q_OBJECT

public:
    pdtwindow(QWidget *parent = 0);
    ~pdtwindow();


private:
    // 初始化工具
    void Init ( void ); 

    // 读pdt.xml
    bool ReadPdtXml( void ); 
    // 读pdt.xml menu
    bool ReadPdtXmlMenu( CXml *pXml ); 
    // 读pdt.xml tool
    bool ReadPdtXmlTool( CXml *pXml ); 
    // 读pdt.xml action
    bool ReadPdtXmlAct( CXml *pXml ); 
    // 读pdt.xml confunc
    bool ReadPdtXmlConFunc( CXml *pXml ); 

    //初始化ui
    bool InitUi( void ); 
    //添加状态栏
    bool InitStatus( void ); 
    //初始化动作
    bool InitAct( void ); 
    //添加菜单
    bool InitMenu( void ); 
    //添加工具栏
    bool InitToolBar( void ); 
    //添加connect func功能
    bool AddConFunc( void );

public:
    PDT m_pdt;                                  /* 结构体 */
    QStatusBar *m_statusBar;                     /* 状态栏 */
    QAction ***m_action;                         /* 动作 */
    QMenu **m_menu;                             /* 菜单栏 */
    QToolBar *m_toolbar;                        /* 工具栏 */


    CPrjNew *m_prjNew;                          /* 新建工程 */
    CPrjOpen *m_prjOpen;                          /* 打开工程 */

    CDock *m_Dock;                           /* 报文显示 */

    CTab *m_tabData ;                            /* 数据表 */
    ccomm *m_comm;

    
};

#endif // PDTWINDOW_H
