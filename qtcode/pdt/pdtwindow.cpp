#include "pdtwindow.h"
#include	<QDebug>
#include	"./public/cxml.h"
#include	"./public/errormsg.h"


const static QString PDT_XML_PATH = QString( "./config/pdt.xml" ); 
pdtwindow::pdtwindow(QWidget *parent)
    : QMainWindow(parent)
{
    Init( );
    m_comm = new ccomm( this );
}

pdtwindow::~pdtwindow()
{
    if( NULL != m_Dock)
    {
        delete m_Dock; 
        m_Dock = NULL; 
    }

    if( NULL != m_tabData )
    {
        delete m_tabData; 
        m_tabData = NULL; 
    }
    //打开工程
    if( NULL != m_prjOpen )
    {
        delete m_prjOpen; 
        m_prjOpen = NULL; 
    }
    //新建工程
    if( NULL != m_prjNew )
    {
        delete m_prjNew; 
        m_prjNew = NULL; 
    }

    // 工具栏
    if( NULL != m_toolbar )
    {
        delete m_toolbar; 
        m_toolbar = NULL; 
    }

    // 菜单栏
    if( NULL != m_menu )
    {
        delete m_menu; 
        m_menu = NULL; 
    }

    // 动作 
    if( NULL != m_action )
    {
        for( int i=0;  i<m_pdt.menu.num; i++ )
        {
            if( NULL != m_action[i] )
            {
                for( int j=0;  j<m_pdt.action[i].num; j++ )
                {
                    if( NULL != m_action[i][j] )
                    {
                        delete m_action[i][j]; 
                        m_action[i][j] = NULL; 
                    }
                }
                delete m_action[i]; 
                m_action[i] = NULL;
            }
        }
        delete m_action; 
        m_action = NULL; 
    }

    // 状态栏
    if( NULL != m_statusBar )
    {
        delete m_statusBar; 
        m_statusBar = NULL; 
    }

    // 功能配置
    if( NULL != m_pdt.confunc.elemet )
    {
        delete m_pdt.confunc.elemet; 
        m_pdt.confunc.elemet = NULL; 
    }

    // 动作配置
    if( NULL != m_pdt.action )
    {
        for( int i=0; i<m_pdt.menu.num; i++ )
        {
            if( NULL != m_pdt.action[i].elemet)
            {
                delete m_pdt.action[i].elemet; 
                m_pdt.action[i].elemet = NULL; 
            }
        }

        delete m_pdt.action; 
        m_pdt.action = NULL; 
    }

    // 工具配置
    if( NULL != m_pdt.tool.elemet )
    {
        delete m_pdt.tool.elemet; 
        m_pdt.tool.elemet = NULL; 
    }

    // 菜单配置
    if( NULL != m_pdt.menu.elemet )
    {
        delete m_pdt.menu.elemet; 
        m_pdt.menu.elemet = NULL; 
    }
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  pdtwindow
 *      Method:  Init
 * Description:  初始化pdt	
 *		 Input:  void
 *		Return:
 *--------------------------------------------------------------------------------------
 */
void pdtwindow::Init ( void )
{
    // 读配置文件 pdt.xml
    if( !ReadPdtXml(  ) )
    {
        exit( -1 ) ;
    }
    
    //根据配置文件创建窗口
    if( !InitUi(  ) )
    {
        exit( -1 ); 
    }

    //添加connect func 功能
    
}		/* -----  end of method pdtwindow::Init  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  pdtwindow
 *      Method:  ReadPdtXml
 * Description:  读pdt.xml	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool pdtwindow::ReadPdtXml ( void )
{
    CXml xml; 
    if( !xml.OpenXml( PDT_XML_PATH ) )
    {
        printLogs( FROMLOCAL( "error::" ),  FROMLOCAL( "不能打开config/pdt.xml" ) ); 
        return false; 
    }

    xml.GetRoot(  ); 
    if( !ReadPdtXmlMenu( &xml ) )
    {
        xml.CloseXml(  ); 
        return false; 
    }

    if( !ReadPdtXmlTool( &xml ) )
    {
        xml.CloseXml(  ); 
        return false; 
    }

    if( !ReadPdtXmlConFunc( &xml ) )
    {
        xml.CloseXml(  ); 
        return false; 
    }

    if( !ReadPdtXmlAct( &xml ) )
    {
        xml.CloseXml(  ); 
        return false; 
    }

    xml.CloseXml(  ); 
    return true;
}		/* -----  end of method pdtwindow::ReadPdtXml  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  pdtwindow
 *      Method:  ReadPdtXmlMenu
 * Description:  读菜单参数 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool pdtwindow::ReadPdtXmlMenu ( CXml *pXml )
{
    QDomNode node = pXml->GetNode( FROMLOCAL( "menu" ) ) ; 
    PDT_MENU_ELEMET *pElemet = NULL; 
    int num = -1; 
    bool ok; 
    
    if( node.isNull() )
    {
        printLogs( "error::",  "can't find node menu in pdt.xml" );
        return false; 
    }

    m_pdt.menu.num = pXml->GetNodeInfo( node,  "num" ).toInt( &ok,  10 ) ; 
    m_pdt.menu.name = pXml->GetNodeInfo( node,  "name" ); 
    num = m_pdt.menu.num; 

    if( 0 < num )
    {
        m_pdt.menu.elemet = new PDT_MENU_ELEMET[ num ];
        if( NULL  ==  m_pdt.menu.elemet )
        {
            printLogs( "error",  "menu elemet faild to malloc" ); 
            return false; 
        }

        pElemet = m_pdt.menu.elemet; 
    }

    QDomNode elenode = pXml->GetFirstElemet( node ); 
    for( int i=0; i< num  && !elenode.isNull(); i++ )
    {
        pElemet->index =
            pXml->GetNodeElemetInfo( elenode,  "index" ).toInt( &ok,  10 ); 
        pElemet->name =
            pXml->GetNodeElemetInfo( elenode,  "name" );
        pElemet->code =
            pXml->GetNodeElemetInfo( elenode,  "code" );

        qDebug(  )  <<  pElemet->index << pElemet->name  << pElemet->code;
        pElemet ++;
        pXml->ElemetNext( elenode ); 
    }

    printLogs( "msg",  "menu elemet read success" ); 
    return true; 
}		/* -----  end of method pdtwindow::ReadPdtXmlMenu  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  pdtwindow
 *      Method:  ReadPdtXmlTool
 * Description:  读工具栏参数	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool pdtwindow::ReadPdtXmlTool ( CXml *pXml )
{
    QDomNode node = pXml->GetNode( FROMLOCAL( "toolbar" ) ) ; 
    PDT_TOOL_ELEMET *pElemet = NULL; 
    int num = -1; 
    bool ok; 
    
    if( node.isNull() )
    {
        printLogs( "error::",  "can't find node menu in pdt.xml" );
        return false; 
    }

    m_pdt.tool.num = pXml->GetNodeInfo( node,  "num" ).toInt( &ok,  10 ) ; 
    m_pdt.tool.name = pXml->GetNodeInfo( node,  "name" ); 
    m_pdt.tool.menuindex = pXml->GetNodeInfo( node,  "menuindex" ).toInt( &ok,  10 ) ;
    num = m_pdt.tool.num;

    if( 0 < num )
    {
        m_pdt.tool.elemet = new PDT_TOOL_ELEMET[ num ];
        if( NULL  ==  m_pdt.tool.elemet )
        {
            printLogs( "error",  "menu elemet faild to malloc" ); 
            return false; 
        }

        pElemet = m_pdt.tool.elemet; 
    }

    QDomNode elenode = pXml->GetFirstElemet( node ); 
    for( int i=0; i< num  && !elenode.isNull(); i++ )
    {
        pElemet->index =
            pXml->GetNodeElemetInfo( elenode,  "index" ).toInt( &ok,  10 ); 
        pElemet->menuindex =
            pXml->GetNodeElemetInfo( elenode,  "menuindex" ).toInt( &ok,  10 );
        pElemet->elemetindex =
            pXml->GetNodeElemetInfo( elenode,  "elemetindex" ).toInt( &ok, 10);

        qDebug(  )  <<  pElemet->index << pElemet->elemetindex  << pElemet->menuindex;
        pElemet ++;
        pXml->ElemetNext( elenode ); 
    }

    printLogs( "msg",  "tool elemet read success" ); 
    return true;
}		/* -----  end of method pdtwindow::ReadPdtXmlTool  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  pdtwindow
 *      Method:  ReadPdtXmlAct
 * Description:  读动作参数	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool pdtwindow::ReadPdtXmlAct ( CXml *pXml )
{
    PDT_ACTION *paction = NULL; 
    if( 0 < m_pdt.menu.num )
    {
        m_pdt.action = new PDT_ACTION[ m_pdt.menu.num ]; 
        if( NULL == m_pdt.action )
        {
            printLogs( "error::",  "action new faild" );
        }

        paction = m_pdt.action; 
    }
    for( int i=0;  i<m_pdt.menu.num; i++ )
    {
        QDomNode node = pXml->GetNode(  m_pdt.menu.elemet[i].code  ) ;
        PDT_ACTION_ELEMET *pElemet = NULL; 
        int num = -1; 
        bool ok; 

        if( node.isNull() )
        {
            printLogs( "error::",  "can't find node action in pdt.xml" );
            return false; 
        }

        paction->num = pXml->GetNodeInfo( node,  "num" ).toInt( &ok,  10 ) ; 
        num = paction->num; 

        if( 0 < num )
        {
            paction->elemet = new PDT_ACTION_ELEMET[ num ];
            if( NULL  ==  paction->elemet )
            {
                printLogs( "error",  "action elemet faild to malloc" ); 
                return false; 
            }

            pElemet = paction->elemet;
        }

        QDomNode elenode = pXml->GetFirstElemet( node ); 
        for( int i=0; i< num  && !elenode.isNull(); i++ )
        {
            pElemet->index =
                pXml->GetNodeElemetInfo( elenode,  "index" ).toInt( &ok,  10 ); 
            pElemet->name =
                pXml->GetNodeElemetInfo( elenode,  "name" );
            pElemet->pic =
                pXml->GetNodeElemetInfo( elenode,  "pic" );
            pElemet->shortcut =
                pXml->GetNodeElemetInfo( elenode,  "shortcut" );
            pElemet->tips =
                pXml->GetNodeElemetInfo( elenode,  "tips" );

            qDebug(  )  <<  pElemet->index << pElemet->name  << pElemet->pic  << pElemet->shortcut  <<  pElemet->tips;
            pElemet ++;
            pXml->ElemetNext( elenode ); 
        }

        printLogs( "msg",  "act elemet read success" ); 

        paction ++; 

    }
    return true;
}		/* -----  end of method pdtwindow::ReadPdtXmlAct  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  pdtwindow
 *      Method:  ReadPdtXmlConFunc
 * Description:  功能	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool pdtwindow::ReadPdtXmlConFunc ( CXml *pXml )
{
    QDomNode node = pXml->GetNode( FROMLOCAL( "confunc" ) ) ; 
    PDT_CONFUNC_ELEMET *pElemet = NULL; 
    int num = -1; 
    bool ok; 
    
    if( node.isNull() )
    {
        printLogs( "error::",  "can't find node confunc in pdt.xml" );
        return false; 
    }

    m_pdt.confunc.num = pXml->GetNodeInfo( node,  "num" ).toInt( &ok,  10 ) ; 
    m_pdt.confunc.name = pXml->GetNodeInfo( node,  "name" ); 
    num = m_pdt.confunc.num;

    if( 0 < num )
    {
        m_pdt.confunc.elemet = new PDT_CONFUNC_ELEMET[ num ];
        if( NULL  ==  m_pdt.confunc.elemet )
        {
            printLogs( "error",  "confunc elemet faild to malloc" ); 
            return false; 
        }

        pElemet = m_pdt.confunc.elemet; 
    }

    QDomNode elenode = pXml->GetFirstElemet( node ); 
    for( int i=0; i< num  && !elenode.isNull(); i++ )
    {
        pElemet->index =
            pXml->GetNodeElemetInfo( elenode,  "index" ).toInt( &ok,  10 ); 
        pElemet->menuindex =
            pXml->GetNodeElemetInfo( elenode,  "menuindex" ).toInt( &ok,  10 );
        pElemet->elemetindex =
            pXml->GetNodeElemetInfo( elenode,  "elemetindex" ).toInt( &ok, 10);
        pElemet->name =
            pXml->GetNodeElemetInfo( elenode,  "name" );

        qDebug(  )  <<  pElemet->index << pElemet->elemetindex  << pElemet->menuindex;
        pElemet ++;
        pXml->ElemetNext( elenode ); 
    }

    printLogs( "msg",  "confunc elemet read success" ); 
    return true;
}		/* -----  end of method pdtwindow::ReadPdtXmlConFunc  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  pdtwindow
 *      Method:  InitUi
 * Description:  初始化界面	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool pdtwindow::InitUi ( void )
{
    this->resize( 800,  600 ); 
    if( !InitStatus(  ) )
    {
        return false; 
    }

    if( !InitAct(  ) )
    {
        return false; 
    }

    if( !InitMenu(  ) )
    {
       return false;
    }

    if( !InitToolBar(  ) )
    {
       return false;
    }

    if( !AddConFunc(  ) )
    {
        return false; 
    }
    
    return true;
}		/* -----  end of method pdtwindow::InitUi  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  pdtwindow
 *      Method:  InitStatus
 * Description:  状态栏	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool pdtwindow::InitStatus ( void )
{
    m_statusBar = new QStatusBar( this );  
    m_statusBar->setObjectName( FROMLOCAL( "状态栏"));
    this->setStatusBar( m_statusBar);

    return true;
}		/* -----  end of method pdtwindow::InitStatus  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  pdtwindow
 *      Method:  InitAct
 * Description:  动作初始化	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool pdtwindow::InitAct ( void )
{

    PDT_ACTION *paction = m_pdt.action; 

    int num = m_pdt.menu.num; 
    if( 0 < num )
    {
        m_action = new QAction **[ num ]; 
        if( NULL  ==  m_action  )
        {
           printLogs( "error::",  "action new false" ) ; 
           return false; 
        }
    }
    
    for( int i=0;  i< num;  i++ )
    {
        //m_action[i] = new QAction[paction->num]( this );
        m_action[i] = new QAction *[paction->num];
        if( NULL == m_action[i])
        {
            qDebug() << "action new error";
            return false;
        }
        for( int j=0;  j<paction->num; j++ )
        {
            PDT_ACTION_ELEMET *pElemet = paction->elemet;

            m_action[i][j] = new QAction( QIcon( pElemet[j].pic ),  pElemet[j].name,  this ); 
            if( NULL  == m_action[i][j] )
            {
                qDebug() << "action new error";
                return false;
            }

            m_action[i][j]->setShortcut( QKeySequence(  pElemet[j].shortcut ) );
            m_action[i][j]->setStatusTip(pElemet[j].tips);
        }

        paction ++;
    }
    return true;
}		/* -----  end of method pdtwindow::InitAct  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  pdtwindow
 *      Method:  InitMenu
 * Description:  菜单	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool pdtwindow::InitMenu ( void )
{
    // m_menuBar = new QMenuBar( this );
    // m_menuBar->setObjectName( FROMLOCAL( StrTopChar( m_pdt.menu.name ) ) ); 
    // m_menuBar->setGeometry( QRect( 0, 0, 600, 19 ) );
    // this->setMenuBar( m_menuBar ); 
    menuBar(  )->setObjectName( m_pdt.menu.name ); 
    m_menu = new QMenu *[m_pdt.menu.num];
    if( NULL  ==  m_menu )
    {
        qDebug(  )  << "m_menu error"; 
        return false; 
    }

    for( int i=0; i<m_pdt.menu.num; i++ )
    {
        m_menu[i] =  menuBar()->addMenu
            ( m_pdt.menu.elemet[i].name  );
            // ( FROMLOCAL( StrTopChar( m_pdt.menu.elemet[i].name ) ) );
        for( int j=0;  j< m_pdt.action[i].num;  j++ )
        {
            m_menu[i]->addAction( m_action[i][j] );
        }
    }

    return true;
}		/* -----  end of method pdtwindow::InitMenu  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  pdtwindow
 *      Method:  InitToolBar
 * Description:  工具栏 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool pdtwindow::InitToolBar ( void )
{
    m_toolbar = new QToolBar(FROMLOCAL("工具栏"));
    m_toolbar->setObjectName(FROMLOCAL("toolBar"));
    this->addToolBar(Qt::TopToolBarArea, m_toolbar);

    m_menu[m_pdt.tool.menuindex]->addAction(m_toolbar->toggleViewAction());
    m_toolbar->setObjectName( m_pdt.tool.name );
    for( int i=0; i<m_pdt.tool.num; i++ )
    {
        PDT_TOOL_ELEMET *pElemet = &m_pdt.tool.elemet[i];
        m_toolbar->addAction
            ( m_action[pElemet->menuindex][pElemet->elemetindex] ); 
    }

    return true;
}		/* -----  end of method pdtwindow::InitToolBar  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  pdtwindow
 *      Method:  AddConFunc
 * Description: 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool pdtwindow::AddConFunc ( void )
{
    for( int i=0;  i<m_pdt.confunc.num; i++ )
    {
        PDT_CONFUNC_ELEMET *pElemet = &m_pdt.confunc.elemet[i]; 

        qDebug() << pElemet->name << pElemet->menuindex << pElemet->elemetindex;

        //新建工程功能
        if( 0 == pElemet->name.compare( QString( "newProject" ) ) )
        {
            m_prjNew = NULL;
            m_prjNew = new CPrjNew (this) ;
            connect( m_action[pElemet->menuindex][pElemet->elemetindex], 
                    SIGNAL( triggered()) ,
                    m_prjNew, 
                    SLOT( exec() ));
        }

        //打开工程功能
        if( 0 == pElemet->name.compare( QString( "openProject" ) ) )
        {
            m_prjOpen = NULL;
            m_prjOpen = new CPrjOpen (this) ;
            connect( m_action[pElemet->menuindex][pElemet->elemetindex], 
                    SIGNAL( triggered()) ,
                    m_prjOpen, 
                    SLOT( exec() ));
        }

        // 主界面
        m_tabData = NULL; 
        m_tabData = new CTab( this ); 
        //打开报文显示
        if( 0 == pElemet->name.compare( QString( "Dock" ) ) )
        {
            qDebug()<< "msgDock";
            m_Dock = NULL;
            m_Dock = new CDock (this) ;

        }

    }

    return true;
}		/* -----  end of method pdtwindow::AddConFunc  ----- */

