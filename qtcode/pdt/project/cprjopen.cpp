#include "cprjopen.h"
//#include "../../src/template.h"

CPrjOpen::CPrjOpen(QMainWindow *parent)
{
    if(0 == parent)
    {
        return;
    }

    m_mainWindow = parent;
    InitUI();
    SetConnectFunc();
    SetAttri();
}

CPrjOpen::~CPrjOpen()
{
    delete m_labelPrjPath;
    delete m_linePath;
    delete m_buttonPath;
    delete m_buttonOk;
    delete m_buttonCancel;
}

void CPrjOpen::InitUI()
{
    //this = new QDialog(m_mainWindow);
    this->setWindowTitle(FROMLOCAL("打开工程"));
    this->setWindowFlags(this->windowFlags()&~Qt::WindowContextHelpButtonHint);
    this->setWhatsThis(FROMLOCAL("打开工程窗口"));
    this->setFixedSize(350,100);

    m_labelPrjPath = new QLabel(FROMLOCAL("路径:"), this);
    m_labelPrjPath->setGeometry(30,20,30,20);

    m_linePath = new QLineEdit( this );
    m_linePath->setGeometry(80,20,200,20);
    m_linePath->setWhatsThis(FROMLOCAL("填写工程路径"));
    m_linePath->setToolTip(FROMLOCAL("填写工程路径"));
    m_buttonPath = new QPushButton(FROMLOCAL("浏览"),this);
    m_buttonPath->setWhatsThis(FROMLOCAL("通过浏览自动填写工程路径"));
    m_buttonPath->setToolTip(FROMLOCAL("通过浏览自动填写工程路径"));
    m_buttonPath->setGeometry(290,20,50,20);

    m_buttonOk = new QPushButton(FROMLOCAL("确定"),this);
    m_buttonOk->setWhatsThis(FROMLOCAL("确定打开工程"));
    m_buttonOk->setToolTip(FROMLOCAL("确定打开工程"));
    m_buttonOk->setGeometry(100,60,80,30);
    m_buttonCancel = new QPushButton(FROMLOCAL("取消"),this);
    m_buttonCancel->setWhatsThis(FROMLOCAL("取消打开工程"));
    m_buttonCancel->setToolTip(FROMLOCAL("取消打开工程"));
    m_buttonCancel->setGeometry(200,60,80,30);

}

//设置信号和槽功能
void CPrjOpen::SetConnectFunc(void)
{
    //点击浏览->获取路径
    connect(m_buttonPath,SIGNAL(released()), this, SLOT(GetOpenPrj()));
    //保存退出
    connect(m_buttonOk, SIGNAL(released()), this, SLOT(SaveCloseDialog()) );
    //退出
    connect(m_buttonCancel, SIGNAL(released()),this,SLOT(close()) );
}

//设置基本属性
void CPrjOpen::SetAttri()
{
    //设置m_linePath只读
    m_linePath->setReadOnly(true);
}

//槽 保存退出Dialog
void CPrjOpen::SaveCloseDialog(void)
{
    //保存功能
    qDebug("11");
    //关闭Dialog
    this->close();
}

//槽 点击浏览->获取路径
void CPrjOpen::GetOpenPrj(void)
{
    QString strFileName;
   // QString strPrjPath;
    char szLastPath[256] = "C:/Users/mengqp/Desktop/";

    strFileName = QFileDialog::getOpenFileName(this,
                            FROMLOCAL("打开工程"),
                            FROMLOCAL(szLastPath),
                            "*.xml",
                            0);

    m_linePath->setText(strFileName);

    //ReadXmlUnit( strFileName);
    SetPrjParam();
}

//设置各个界面参数
bool CPrjOpen::SetPrjParam( void )
{
    //DATATYPE_UNIT *pUnit = GetUnitArray();

    //DATATYPE_PORT *pPort = &pUnit->port;
    return true;

}
