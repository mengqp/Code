#ifndef CDOCK_H
#define CDOCK_H

#include <QDockWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QTextEdit>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QObject>
#include <QFileDialog>

#include "../public/datatype.h"
#include	"docktype.h"
#include	"../public/cxml.h"

class pdtwindow;
//控件
typedef struct _DOCK_CONTONTROLS 
{
    int buttonNum; 
    int checkNum;


    QPushButton **button;
    int *ibutton;
    QCheckBox **check; 
    int *icheck;

    _DOCK_CONTONTROLS(  )
    {
        buttonNum = 0; 
        checkNum=0; 

        button = NULL; 
        check = NULL; 
    }

}DOCK_CONTONTROLS;				/* ----------  end of struct DockControls  ---------- */


//edit 属性
typedef struct _DOCK_EDIT_ATTR
{
    bool isValue;
    bool isHex; 
    bool isStop; 
    bool isSave; 
    QString file_name; 

    _DOCK_EDIT_ATTR()
    {
        isHex = false; 
        isStop = false; 
        isSave = false; 
        file_name = QString( "" ); 
    }
}DOCK_EDIT_ATTR;				/* ----------  end of struct DOCK_EDIT_ATTR  ---------- */

class CDock : public QObject
{
    Q_OBJECT
public:
    explicit CDock(QMainWindow *parent = 0);
    virtual ~CDock();

public:


private:
    // 初始化
    void Init( void );
    // 读配置
    bool ReadDockXml( void ); 
    // 读dockinfo
    bool ReadDockXmlInfo( CXml *pXml );
    // 读dockwidget
    bool ReadDockXmlWidget( CXml *pXml ); 
    // 读编辑显示区
    bool ReadDockXmlEdit( CXml *pXml ); 
    // 读编缉区颜色
    bool ReadDockXmlColor( CXml *pXml ); 
    // 读连接功能
    bool ReadDockXmlConFunc( CXml *pXml );
    // 初始化界面
    bool InitUi();
    // 初始化窗口
    bool InitWidget( void ); 
    // 初始化控件
    bool InitControls( void ); 
    bool GetXmlControlsNum ( void );
    //初始化功能
    bool InitConFunc( void ); 

    //设置信号和槽功能
    void SetConnectFunc(void);
    //设置基本属性
    void SetAttri();
    void WriteEdit ( int index,  QString str,  DOCK_EDIT_ATTR *attr );
public:
    QDockWidget **m_dockWidget;
    QWidget **m_widget; 
    QTextEdit **m_edit; 
    DOCK m_dock;
    DOCK_CONTONTROLS *m_ctl; 
    DOCK_EDIT_ATTR *m_editAttr; 

private:
    //定义主窗口
    pdtwindow *m_mainWindow;

    QHBoxLayout **m_btnLayout;
    QVBoxLayout **m_viewLayout;

private slots:
    //暂停
    void EditPauseSlot(void);
    //保存
    void EditSaveSlot(void);
    //16进制
    void EditIsHexSlot(void);
};

#endif // CMSGDOCK_H
