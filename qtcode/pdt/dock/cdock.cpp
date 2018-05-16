#include "cdock.h"
#include	"../public/errormsg.h"
#include "../pdtwindow.h"
#include <QDateTime>





CDock::CDock(QMainWindow *parent/* = 0*/)
{
    if(0 == parent)
    {
        return;
    }
    m_mainWindow = (pdtwindow *)parent;

    Init(  ); 
}

CDock::~CDock()
{
    for( int i=0; i<m_dock.info.num; i++ )
    {
        for( int j=0; j<m_ctl[i].buttonNum; j++ )
        {
            if( NULL != m_ctl[i].button[j] )
            {
                delete m_ctl[i].button[j]; 
                m_ctl[i].button[j] = NULL; 
            }

            if( NULL != m_ctl[i].check[j] )
            {
                delete m_ctl[i].check[j] ; 
                m_ctl[i].check[j] = NULL; 
            }
        }
    }
    for( int i=0; i<m_dock.info.num; i++ )
    {
        if( NULL != m_btnLayout[i] )
        {
            delete m_btnLayout[i]; 
            m_btnLayout[i] = NULL;
        }

        if( NULL != m_viewLayout[i] )
        {
            delete m_viewLayout[i];
            m_viewLayout[i] = NULL; 
        }

    }
    if( NULL != m_viewLayout )
    {
        delete m_viewLayout; 
        m_viewLayout = NULL; 
    }

    if( NULL != m_btnLayout )
    {
        delete m_btnLayout; 
        m_btnLayout = NULL; 
    }

    for( int i=0; i<m_dock.info.num; i++ )
    {
        if( NULL != m_ctl[i].button )
        {
            delete m_ctl[i].button; 
            m_ctl[i].button = NULL; 
        }

        if( NULL != m_ctl[i].check )
        {
            delete m_ctl[i].check; 
            m_ctl[i].check = NULL; 
        }

        if( NULL != m_ctl[i].ibutton )
        {
            delete m_ctl[i].ibutton; 
            m_ctl[i].ibutton = NULL; 
        }
        if( NULL != m_ctl[i].icheck )
        {
            delete m_ctl[i].icheck; 
            m_ctl[i].icheck = NULL; 
        }
    }

    if( NULL != m_editAttr )
    {
        delete m_editAttr; 
        m_editAttr = NULL; 
    }

    if( NULL != m_ctl )
    {
        delete m_ctl; 
        m_ctl = NULL; 
    }

    for( int i=0; i<m_dock.info.num; i++ )
    {
        if( NULL != m_edit[i] )
        {
            delete m_edit[i]; 
            m_edit[i] = NULL; 
        }

        if( NULL != m_widget[i] )
        {
            delete m_widget[i]; 
            m_widget[i] = NULL;
        }

        if( NULL != m_dockWidget[i] )
        {
            delete m_dockWidget[i]; 
            m_dockWidget[i] = NULL; 
        }
    }
    if( NULL != m_edit )
    {
        delete m_edit; 
        m_edit = NULL; 
    }

    if( NULL != m_widget )
    {
        delete m_widget; 
        m_widget = NULL; 
    }

    if( NULL != m_dockWidget )
    {
        delete m_dockWidget; 
        m_dockWidget = NULL; 
    }

    if( NULL != m_dock.confunc.elemet )
    {
        delete m_dock.confunc.elemet; 
        m_dock.confunc.elemet = NULL; 
    }
    if( NULL != m_dock.color.elemet )
    {
        delete m_dock.color.elemet; 
        m_dock.color.elemet = NULL; 
    }

    for( int i=0; i<m_dock.info.num; i++ )
    {
        if( NULL != m_dock.widget[i].elemet)
        {
            delete m_dock.widget[i].elemet; 
            m_dock.widget[i].elemet = NULL; 
        }
    }
    if( NULL != m_dock.widget )
    {
        delete m_dock.widget; 
        m_dock.widget = NULL; 
    }

    if( NULL  != m_dock.info.elemet   )
    {
        delete m_dock.info.elemet; 
        m_dock.info.elemet = NULL; 
    }

    // delete m_editClear;
    // delete  m_editPause;
    // delete  m_editSave;
    // delete m_viewEdit;
    // delete m_editIsHex;

    // delete m_btnLayout;
    // delete m_viewLayout;
    // delete m_viewWidget;
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CDock
 *      Method:  Init
 * Description:  初始化	
 *		 Input:  void
 *		Return:  void
 *--------------------------------------------------------------------------------------
 */
void CDock::Init ( void )
{
    if( !ReadDockXml(  ) )
    {
        exit( -2 ); 
    }

    if( !InitUi(  ) )
    {
        exit( -2 ); 
    }
}		/* -----  end of method CDock::Init  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CDock
 *      Method:  ReadDockXml
 * Description:  读Dock配置文件
 *		 Input:  void
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CDock::ReadDockXml ( void )
{
    CXml xml; 
    if( !xml.OpenXml( DOCK_XML_PATH ) )
    {
        printLogs( FROMLOCAL( "error::" ),  FROMLOCAL( "不能打开config/pdt.xml" ) ); 
        return false; 
    }

    xml.GetRoot(  ); 

    if( !ReadDockXmlInfo( &xml ) )
    {
        xml.CloseXml(  );
        return false; 
    }

    if( !ReadDockXmlWidget( &xml ) )
    {
        xml.CloseXml(  ); 
        return false; 
    }

    if( !ReadDockXmlEdit( &xml  ) )
    {
        xml.CloseXml(); 
        return false; 
    }

    if( !ReadDockXmlColor( &xml ) )
    {
        xml.CloseXml(  ); 
        return false; 
    }

    if( !ReadDockXmlConFunc(&xml  ) )
    {
        xml.CloseXml(  ); 
        return false; 
    }

    xml.CloseXml(  ); 
    return true;
}		/* -----  end of method CDock::ReadDockXml  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CDock
 *      Method:  ReadDockXmlInfo
 * Description:  读窗口的基本信息	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CDock::ReadDockXmlInfo ( CXml *pXml )
{
    QDomNode node = pXml->GetNode( FROMLOCAL( "info" ) ) ; 
    DOCK_INFO_ELEMET *pElemet = NULL; 
    int num = -1; 
    bool ok; 

    if( node.isNull() )
    {
        printLogs( "error::",  "can't find node info in pdt.xml" );
        return false; 
    }

    m_dock.info.num = pXml->GetNodeInfo( node,  "num" ).toInt( &ok,  10 ) ; 
    num = m_dock.info.num; 

    if( 0 < num )
    {
        m_dock.info.elemet = new DOCK_INFO_ELEMET[ num ];
        if( NULL  ==  m_dock.info.elemet )
        {
            printLogs( "error",  "info elemet faild to malloc" ); 
            return false; 
        }

        pElemet = m_dock.info.elemet; 
    }

    QDomNode elenode = pXml->GetFirstElemet( node ); 
    for( int i=0; i< num  && !elenode.isNull(); i++ )
    {
        pElemet->index =
            pXml->GetNodeElemetInfo( elenode,  "index" ).toInt( &ok,  10 ); 
        pElemet->name =
            pXml->GetNodeElemetInfo( elenode,  "name" );
        pElemet->widget =
            pXml->GetNodeElemetInfo( elenode,  "widget" );

        qDebug(  )  <<  pElemet->index << pElemet->name  << pElemet->widget;
        pElemet ++;
        pXml->ElemetNext( elenode ); 
    }

    printLogs( "msg",  "info elemet read success" ); 
    return true; 

}		/* -----  end of method CDock::ReadDockXmlInfo  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CDock
 *      Method:  ReadDockXmlWidget
 * Description:  读每个窗口的信息	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CDock::ReadDockXmlWidget ( CXml *pXml )
{
    if( 0 < m_dock.info.num  )
    {
        m_dock.widget = new DOCK_WIDGET[m_dock.info.num];
        if( NULL  ==  m_dock.widget )
        {
            return false;
        }
    }
    for( int i=0; i<m_dock.info.num;i++)
    {
        QDomNode node = pXml->GetNode( m_dock.info.elemet[i].widget ) ;
        DOCK_WIDGET_ELEMET *pElemet = NULL;
        int num = -1;
        bool ok;

        if( node.isNull() )
        {
            printLogs( "error::",  "can't find node widget in pdt.xml" );
            return false;
        }

        m_dock.widget[i].num = pXml->GetNodeInfo( node,  "num" ).toInt( &ok,  10 ) ;
        num = m_dock.widget[i].num;

        if( 0 < num )
        {
            m_dock.widget[i].elemet = new DOCK_WIDGET_ELEMET[ num ];
            if( NULL  ==  m_dock.widget[i].elemet )
            {
                printLogs( "error",  "widget elemet faild to malloc" );
                return false;
            }

            pElemet = m_dock.widget[i].elemet;
        }

        QDomNode elenode = pXml->GetFirstElemet( node );
        for( int i=0; i< num  && !elenode.isNull(); i++ )
        {
            pElemet->index =
                pXml->GetNodeElemetInfo( elenode,  "index" ).toInt( &ok,  10 );
            pElemet->name =
                pXml->GetNodeElemetInfo( elenode,  "name" );
            pElemet->funcindex =
                pXml->GetNodeElemetInfo( elenode,  "funcindex" ).toInt(&ok, 10);

            qDebug(  )  <<  pElemet->index << pElemet->name  << pElemet->funcindex;
            pElemet ++;
            pXml->ElemetNext( elenode );
        }

        printLogs( "msg",  "widget elemet read success" );

    }
    return true; 
}		/* -----  end of method CDock::ReadDockXmlWidget  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  CDock
 *      Method:  ReadDockXmlEdit
 * Description:  读显示编绎区	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CDock::ReadDockXmlEdit ( CXml *pXml )
{
    QDomNode node = pXml->GetNode( FROMLOCAL( "edit" ) ) ; 
    bool ok; 

    if( node.isNull() )
    {
        printLogs( "error::",  "can't find node edit in pdt.xml" );
        return false; 
    }

    m_dock.edit.name = pXml->GetNodeInfo( node,  "name" ) ;
    m_dock.edit.readonly = pXml->GetNodeInfo( node,  "readonly" ).toInt( &ok,  10 ) ; 
    m_dock.edit.maxrow = pXml->GetNodeInfo( node,  "maxrow" ).toInt( &ok,  10 ) ; 

    printLogs( "msg",  "edit elemet read success" ); 

    return true;
}		/* -----  end of method CDock::ReadDockXmlEdit  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  CDock
 *      Method:  ReadDockXmlColor
 * Description:  编辑区颜色 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CDock::ReadDockXmlColor ( CXml *pXml )
{
    QDomNode node = pXml->GetNode( FROMLOCAL( "color" ) ) ; 
    DOCK_COLOR_ELEMET *pElemet = NULL; 
    int num = -1; 
    bool ok; 

    if( node.isNull() )
    {
        printLogs( "error::",  "can't find node color in pdt.xml" );
        return false; 
    }

    m_dock.color.num = pXml->GetNodeInfo( node,  "num" ).toInt( &ok,  10 ) ; 
    num = m_dock.color.num; 

    if( 0 < num )
    {
        m_dock.color.elemet = new DOCK_COLOR_ELEMET[ num ];
        if( NULL  ==  m_dock.color.elemet )
        {
            printLogs( "error",  "color elemet faild to malloc" ); 
            return false; 
        }

        pElemet = m_dock.color.elemet; 
    }

    QDomNode elenode = pXml->GetFirstElemet( node ); 
    for( int i=0; i< num  && !elenode.isNull(); i++ )
    {
        pElemet->index =
            pXml->GetNodeElemetInfo( elenode,  "index" ).toInt( &ok,  10 ); 
        pElemet->name =
            pXml->GetNodeElemetInfo( elenode,  "name" );
        pElemet->funcname =
            pXml->GetNodeElemetInfo( elenode,  "funcname" );

        qDebug(  )  <<  pElemet->index << pElemet->name  << pElemet->funcname;
        pElemet ++;
        pXml->ElemetNext( elenode ); 
    }

    printLogs( "msg",  "color elemet read success" ); 
    return true;
}		/* -----  end of method CDock::ReadDockXmlColor  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CDock
 *      Method:  ReadDockXmlConFunc
 * Description:  connect 功能信息
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CDock::ReadDockXmlConFunc ( CXml *pXml )
{
    QDomNode node = pXml->GetNode( FROMLOCAL( "confunc" ) ) ; 
    DOCK_CONFUNC_ELEMET *pElemet = NULL; 
    int num = -1; 
    bool ok; 

    if( node.isNull() )
    {
        printLogs( "error::",  "can't find node confunc in pdt.xml" );
        return false; 
    }

    m_dock.confunc.num = pXml->GetNodeInfo( node,  "num" ).toInt( &ok,  10 ) ; 
    num = m_dock.confunc.num; 
    m_dock.confunc.name = pXml->GetNodeInfo( node,  "name" ); 
    num = m_dock.confunc.num; 

    if( 0 < num )
    {
        m_dock.confunc.elemet = new DOCK_CONFUNC_ELEMET[ num ];
        if( NULL  ==  m_dock.confunc.elemet )
        {
            printLogs( "error",  "confunc elemet faild to malloc" ); 
            return false; 
        }

        pElemet = m_dock.confunc.elemet; 
    }

    QDomNode elenode = pXml->GetFirstElemet( node ); 
    for( int i=0; i< num  && !elenode.isNull(); i++ )
    {
        pElemet->index =
            pXml->GetNodeElemetInfo( elenode,  "index" ).toInt( &ok,  10 ); 
        pElemet->name =
            pXml->GetNodeElemetInfo( elenode,  "name" );
        pElemet->wide =
            pXml->GetNodeElemetInfo( elenode,  "wide" ).toInt( &ok,  10 );
        pElemet->type =
            pXml->GetNodeElemetInfo( elenode,  "type" );

        qDebug(  )  <<  pElemet->index << pElemet->name  << pElemet->type;
        pElemet ++;
        pXml->ElemetNext( elenode ); 
    }

    printLogs( "msg",  "confunc elemet read success" ); 

    return true;
}		/* -----  end of method CDock::ReadDockXmlConFunc  ----- */


bool CDock::InitUi()
{
    if( !InitWidget(  ) )
    {
        return false; 
    }

    if( !InitControls(  ) )
    {
        return false;
    }

    if( !InitConFunc() )
    {
         return false;
    }
    // this->setWindowTitle(FROMLOCAL("报文显示"));
    // m_mainWindow->addDockWidget(Qt::BottomDockWidgetArea,this);

    // m_viewWidget = new QWidget(this);
    // this->setWidget(m_viewWidget);

    // m_editClear = new QPushButton(FROMLOCAL("清空"),m_viewWidget);
    // m_editClear->setMaximumWidth(40);
    // m_editClear->setFlat(true);

    // m_editPause = new QPushButton(FROMLOCAL("暂停"),m_viewWidget);
    // m_editPause->setMaximumWidth(40);
    // m_editPause->setFlat(true);

    // m_editSave = new QPushButton(FROMLOCAL("保存"),m_viewWidget);
    // m_editSave->setMaximumWidth(40);
    // m_editSave->setFlat(true);

    // m_editIsHex = new QCheckBox(FROMLOCAL("16进制"),m_viewWidget);
    // m_editIsHex->setMaximumWidth(60);
    // m_editIsHex->setChecked(true);

    // m_viewEdit = new QTextEdit(m_viewWidget);
    // m_viewEdit->setReadOnly(true);
    // m_viewEdit->append(FROMLOCAL("报文显示"));
    // //设置最大行数
    // m_viewEdit->document()->setMaximumBlockCount(1500);

    // m_btnLayout = new QHBoxLayout();
    // m_btnLayout->setAlignment(Qt::AlignLeft);
    // m_btnLayout->addWidget(m_editClear);
    // m_btnLayout->addWidget(m_editPause);
    // m_btnLayout->addWidget(m_editSave);
    // m_btnLayout->addWidget(m_editIsHex);

    // m_viewLayout = new QVBoxLayout(m_viewWidget);
    // m_viewLayout->setSpacing(0);
    // m_viewLayout->setMargin(0);
    // m_viewLayout->addLayout(m_btnLayout);
    // m_viewLayout->addWidget(m_viewEdit);
    return true;
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CDock
 *      Method:  InitWidget
 * Description:  初始化界面	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CDock::InitWidget ( void )
{
    int menuindex = 4;
    for( int i=0; i< m_mainWindow->m_pdt.confunc.num;i++)
    {
        PDT_CONFUNC_ELEMET *pElemet = &m_mainWindow->m_pdt.confunc.elemet[i];
        if( 0 == pElemet->name.compare("Dock"))
        {
            menuindex = pElemet->menuindex;
        }
    }
    if( 0 < m_dock.info.num )
    {
        m_dockWidget = new QDockWidget *[m_dock.info.num];
        if( NULL  ==  m_dockWidget )
        {
            return false; 
        }


        m_widget = new QWidget*[m_dock.info.num];
        if( NULL  ==  m_widget )
        {
            return false;
        }

        m_edit = new QTextEdit *[m_dock.info.num];
        if( NULL  ==  m_edit )
        {
            return false;
        }
    }
    for( int i=0; i<m_dock.info.num; i++ )
    {
        m_dockWidget[i] = new QDockWidget( m_mainWindow ); 

        m_dockWidget[i]->setWindowTitle( m_dock.info.elemet[i].name );
        m_mainWindow->addDockWidget( Qt::BottomDockWidgetArea, m_dockWidget[i] );

        m_widget[i] = new QWidget( m_dockWidget[i] );
        if( NULL == m_widget[i])
        {
            return false;
        }
        m_dockWidget[i]->setWidget( m_widget[i] );

        m_edit[i] = new QTextEdit( m_widget[i] );
        m_edit[i]->setReadOnly( m_dock.edit.readonly );
        m_edit[i]->append(  m_dock.info.elemet[i].name );
        m_edit[i]->document()->setMaximumBlockCount( m_dock.edit.maxrow );

        if( i  >= 1 )
        {
            m_mainWindow->tabifyDockWidget( m_dockWidget[i-1],
                    m_dockWidget[i] );
        }

        m_mainWindow->m_menu[menuindex]->addAction( m_dockWidget[i]->toggleViewAction() );

    }

    return true;
}		/* -----  end of method CDock::InitWidget  ----- */



/*
 *--------------------------------------------------------------------------------------
 *       Class:  CDock
 *      Method:  GetXmlControlsNum
 * Description:  获得xml中button 和 check 数量 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CDock::GetXmlControlsNum ( void )
{
    ( m_ctl ) = new DOCK_CONTONTROLS [ m_dock.info.num ];
    if( NULL == ( m_ctl ) )
    {
        return false;
    }
    
    m_editAttr = new DOCK_EDIT_ATTR[ m_dock.info.num ]; 
    if( NULL  ==  m_editAttr )
    {
        return false; 
    }

    for( int i=0;  i<m_dock.info.num; i++ )
    {
        DOCK_CONTONTROLS *pCtl = &m_ctl[i];
        ( pCtl )->buttonNum = 0;
        ( pCtl ) ->checkNum = 0;

        for( int j=0; j<m_dock.widget[i].num; j++ )
        {
            int funcindex = m_dock.widget[i].elemet[j].funcindex;
            if( funcindex >= m_dock.confunc.num )
            {
                return false;
            }

            if( 0  ==  m_dock.confunc.elemet[ funcindex ].type.compare( "pushButton" ) )
            {
                ( pCtl)->buttonNum++;
            }

            if( 0  ==  m_dock.confunc.elemet[ funcindex ].type.compare( "checkBox" ) )
            {
                ( pCtl)->checkNum++;
            }

            (pCtl)->button = new QPushButton *[(pCtl)->buttonNum];
            (pCtl)->check = new QCheckBox *[(pCtl)->checkNum];
            pCtl->ibutton = new int[pCtl->buttonNum];
            pCtl->icheck = new int[pCtl->checkNum];
        }

    }

    return true;
}		/* -----  end of method CDock::GetXmlControlsNum  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CDock
 *      Method:  InitControls
 * Description:  初始化控件	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CDock::InitControls ( void )
{

    if( !GetXmlControlsNum(  ) )
    {
        return false;
    }

    qDebug() << m_ctl[0].checkNum;

    m_btnLayout = new QHBoxLayout*[m_dock.info.num] ;
    m_viewLayout = new QVBoxLayout *[m_dock.info.num];

    for( int i=0; i<m_dock.info.num; i++ )
    {
        int ibutton = 0;
        int icheck = 0;

        m_btnLayout[i] = new QHBoxLayout();
        m_btnLayout[i]->setAlignment(Qt::AlignLeft);

        m_viewLayout[i] = new QVBoxLayout(m_widget[i]);

        for( int k=0; k<m_dock.confunc.num;k++)
        {
            for( int j=0; j<m_dock.widget[i].num;  j++)
            {
                if( m_dock.widget[i].elemet[j].funcindex == m_dock.confunc.elemet[k].index)
                {
                    if( 0 == m_dock.confunc.elemet[k].type.compare("pushButton"))
                    {
                        m_ctl[i].button[ibutton] = new QPushButton( m_dock.widget[i].elemet[j].name, m_widget[i] );
                        m_ctl[i].button[ibutton]->setMaximumWidth( m_dock.confunc.elemet[k].wide);
                        m_ctl[i].button[ibutton]->setFlat( true );
                        m_ctl[i].ibutton[ibutton] = m_dock.confunc.elemet[k].index;
                        m_btnLayout[i]->addWidget(m_ctl[i].button[ibutton]);
                        ibutton ++;
                    }

                    if( 0 == m_dock.confunc.elemet[k].type.compare("checkBox"))
                    {
                        m_ctl[i].check[icheck] = new QCheckBox( m_dock.widget[i].elemet[j].name, m_widget[i] );
                        m_ctl[i].check[icheck]->setMaximumWidth( m_dock.confunc.elemet[k].wide);
                        m_ctl[i].check[icheck]->setChecked(true);
                        m_ctl[i].icheck[icheck] = m_dock.confunc.elemet[k].index;
                        m_btnLayout[i]->addWidget(m_ctl[i].check[icheck]);
                        icheck ++;
                    }
                }

            }
        }

        m_viewLayout[i]->setSpacing(0);
        m_viewLayout[i]->setMargin(0);
        m_viewLayout[i]->addLayout(m_btnLayout[i]);
        m_viewLayout[i]->addWidget(m_edit[i]);


    }

    return true;
}		/* -----  end of method CDock::InitControls  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CDock
 *      Method:  InitConFunc
 * Description:  初始化信号和槽	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CDock::InitConFunc ( void )
{
    for( int i=0; i<m_dock.info.num;i++)
    {
        for( int j=0; j<m_dock.confunc.num; j++)
        {
            if( 0 == m_dock.confunc.elemet[j].name.compare(QString("clearEdit")) )
            {
                for( int k=0; k<m_ctl[i].buttonNum;k++)
                {
                    if( m_ctl[i].ibutton[k] == m_dock.confunc.elemet[j].index)
                    {
                        connect(m_ctl[i].button[k], SIGNAL(released()), m_edit[i], SLOT(clear()));
                        break;
                    }

                }
            }

            for( int k=0; k<m_ctl[i].checkNum;k++)
            {
                if( m_ctl[i].icheck[k] == m_dock.confunc.elemet[j].index)
                {
                    if( 0 == m_dock.confunc.elemet[j].name.compare(QString("stopEdit")) )
                    {
                        connect(m_ctl[i].check[k], SIGNAL(released()), this, SLOT(EditPauseSlot( )));
                    }

                    if( 0 == m_dock.confunc.elemet[j].name.compare(QString("saveEdit")) )
                    {
                        connect(m_ctl[i].check[k], SIGNAL(released()), this, SLOT(EditSaveSlot( )));
                    }

                    if( 0 == m_dock.confunc.elemet[j].name.compare(QString("isHex")) )
                    {
                        connect(m_ctl[i].check[k], SIGNAL(released()), this, SLOT(EditIsHexSlot()));
                    }

                }
            }
        }
    }
    return true;
}		/* -----  end of method CDock::InitConFunc  ----- */

//设置基本属性
void CDock::SetAttri()
{
    //设置m_linePath只读
    //m_linePath->setReadOnly(true);
}

//槽 暂停
void CDock::EditPauseSlot(void)
{
    QObject* send=QObject::sender();
    for(int i=0;i<m_dock.info.num;i++)
    {
        for( int j=0; j<m_ctl[i].checkNum; j++)
        {
            if(send==((QObject*)m_ctl[i].check[j]))
            {
                if( m_ctl[i].check[j]->isChecked())
                {
                    m_edit[i]->append("zt");
                    m_editAttr[i].isStop = true; 
                }
                else
                {
                    m_edit[i]->append("nzt");
                    m_editAttr[i].isStop = false; 
                }
            }
        }
    }

}

//槽 保存
void CDock::EditSaveSlot(void)
{
    QObject* send=QObject::sender();
    for(int i=0;i<m_dock.info.num;i++)
    {
        for( int j=0; j<m_ctl[i].checkNum; j++)
        {
            if(send==((QObject*)m_ctl[i].check[j]))
            {
                if( m_ctl[i].check[j]->isChecked())
                {
                    m_edit[i]->append("bc");
                    QString file_name; 
                    file_name = QFileDialog::getSaveFileName(m_dockWidget[i],
                            tr("Save File"),
                            "./save",
                            "*.txt",
                            0);
                    if (!file_name.isNull())
                    {
                        qDebug()<<file_name;
                        //fileName是文件名
                        QFile file(file_name);
                        if (!file.open(QFile::WriteOnly | QFile::Text)) 
                        {
                            QMessageBox::warning(m_dockWidget[i], tr("Recent Files"),
                                    tr("Cannot write file %1:\n%2.")
                                    .arg(file_name)
                                    .arg(file.errorString()));

                            //file.write("hello world!\n");
                            return;
                        }
                        m_editAttr[i].isSave = true; 
                        file.close();

                        m_editAttr[i].file_name = file_name; 
                    }
                    else
                    {
                        m_ctl[i].check[j]->setChecked( false ); 
                    }
                }
                else
                {
                    m_edit[i]->append("nbc");
                    m_editAttr[i].isSave = false; 
                }


            }
        }
    }
}

//
//槽 保存
void CDock::EditIsHexSlot(void)
{
    QObject* send=QObject::sender();
    for(int i=0;i<m_dock.info.num;i++)
    {
        for( int j=0; j<m_ctl[i].checkNum; j++)
        {
            if(send==((QObject*)m_ctl[i].check[j]))
            {
                if( m_ctl[i].check[j]->isChecked())
                {
                    m_edit[i]->append("16进制");
                    m_editAttr[i].isHex = true;
                    WriteEdit(i,QString("20"),NULL);
                }
                else
                {
                    m_edit[i]->append("ascII");
                    m_editAttr[i].isHex = false ; 
                }
            }
        }
    }
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CDock
 *      Method:  WriteEdit
 * Description: 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
void CDock::WriteEdit ( int index,  QString str,  DOCK_EDIT_ATTR *attr )
{
    if( index  >=  m_dock.info.num
            || index < 0)
    {
        return; 
    }

    if( NULL  ==  attr )
    {
        attr = &m_editAttr[index];
    }

    QDateTime curDateTime = QDateTime::currentDateTime();
    QString curDate = curDateTime.toString("yyyy-MM-dd-hh-mm-ss:");

    if( attr->isStop )
    {
        return; 
    }

    QString strHex;
    strHex += curDate;

    if(attr->isHex )
    {
        qDebug()<<"16";
        //写16进制

        strHex += str;
    }
    else
    {
        strHex += str;
    }

    if( attr->isSave )
    {
        QString file_name = m_editAttr[index].file_name; 

        if (!file_name.isNull())
        {
            //fileName是文件名
            QFile file(file_name);
            if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Append)) {
                QMessageBox::warning(m_dockWidget[index], tr("Recent Files"),
                        tr("Cannot write file %1:\n%2.")
                        .arg(file_name)
                        .arg(file.errorString()));

                return;
            }

            QTextStream out(&file);
            out<<strHex<<endl;
            file.close();

        }

    }

    m_edit[index]->append( strHex ); 
    return ;
}		/* -----  end of method CDock::WriteEdit  ----- */

