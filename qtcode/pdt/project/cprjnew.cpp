#include "cprjnew.h"

CPrjNew::CPrjNew(QMainWindow *parent)
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

CPrjNew::~CPrjNew()
{

    delete m_labelPrjName;
    delete m_labelPrjPath;
    delete m_lineName;
    delete m_linePath;
    delete m_buttonPath;
    delete m_buttonOk;
    delete m_buttonCancel;

}

void CPrjNew::InitUI()
{
    this->setWindowTitle(FROMLOCAL("新建工程"));
    this->setWindowFlags(this->windowFlags()&~Qt::WindowContextHelpButtonHint);
    this->setWhatsThis(FROMLOCAL("新建工程窗口"));
    this->setFixedSize(350,200);

    m_labelPrjName = new QLabel(FROMLOCAL("名称:"), this);
    m_labelPrjName->setGeometry(30,50,30,20);
    m_labelPrjPath = new QLabel(FROMLOCAL("路径:"), this);
    m_labelPrjPath->setGeometry(30,100,30,20);

    m_lineName = new QLineEdit( this );
    m_lineName->setGeometry(80,50,200,20);
    m_lineName->setWhatsThis(FROMLOCAL("填写工程名称"));
    m_lineName->setToolTip(FROMLOCAL("填写工程名称"));
    m_linePath = new QLineEdit( this );
    m_linePath->setGeometry(80,100,200,20);
    m_linePath->setWhatsThis(FROMLOCAL("填写工程路径"));
    m_linePath->setToolTip(FROMLOCAL("填写工程路径"));
    m_buttonPath = new QPushButton(FROMLOCAL("浏览"),this);
    m_buttonPath->setWhatsThis(FROMLOCAL("通过浏览自动填写工程路径"));
    m_buttonPath->setGeometry(290,100,50,20);
    m_buttonPath->setToolTip(FROMLOCAL("通过浏览自动填写工程路径"));

    m_buttonOk = new QPushButton(FROMLOCAL("确定"),this);
    m_buttonOk->setWhatsThis(FROMLOCAL("确定新建工程"));
    m_buttonOk->setToolTip(FROMLOCAL("确定新建工程"));
    m_buttonOk->setGeometry(100,150,80,30);
    m_buttonCancel = new QPushButton(FROMLOCAL("取消"),this);
    m_buttonCancel->setWhatsThis(FROMLOCAL("取消新建工程"));
    m_buttonCancel->setToolTip(FROMLOCAL("取消新建工程"));
    m_buttonCancel->setGeometry(200,150,80,30);
}

//设置信号和槽功能
void CPrjNew::SetConnectFunc(void)
{
    //点击浏览->获取路径
    connect(m_buttonPath,SIGNAL(released()), this, SLOT(GetOpenPrj()));
    //保存退出
    connect(m_buttonOk, SIGNAL(released()), this, SLOT(SaveCloseDialog()) );
    //退出
    connect(m_buttonCancel, SIGNAL(released()),this,SLOT(close()) );
}

//设置基本属性
void CPrjNew::SetAttri()
{
    //设置m_linePath只读
    //m_linePath->setReadOnly(true);
}

//槽 保存退出Dialog
void CPrjNew::SaveCloseDialog(void)
{
    //保存功能
    qDebug("11");
    //关闭Dialog
    this->close();
}

//槽 点击浏览->获取路径
void CPrjNew::GetOpenPrj(void)
{
    QString strFileName;
   // QString strPrjPath;
    char szLastPath[256] = "";

    strFileName = QFileDialog::getExistingDirectory(this,
                            FROMLOCAL("新建工程路径"),
                            szLastPath,
                            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    m_linePath->setText(strFileName);

}
