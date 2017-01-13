#include "widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    InitUi();
    InitUiFeature();
    InitUiParam();
}

Widget::~Widget()
{
    delete m_dataFloatLabel;
    delete m_dataHexLabel;

    delete m_HexSelButtonGroup;
   // delete m_ByteSelButtonGroup;
   // delete m_ByteButton;
   // delete m_WordButton;
   // delete m_DwordButton;
    delete m_dataFlaotButton;
    delete m_dataHexButton;
    delete m_dataHexAButton;
    delete m_dataHexBButton;

    delete  m_dataWriteEdit;
    delete  m_dataFloatEdit;
    delete  m_dataHexEdit;

    delete m_converButton;

    delete m_pConversion;

    delete m_pRegExp;

    //delete m_clearWriteButton;

}

bool Widget::InitUi()
{


    //创建控件 Label
    m_dataFloatLabel = new QLabel(this);
    m_dataFloatLabel->setGeometry(50,100,200,20);
    m_dataFloatLabel->setText(FROMLOCAL("浮点"));

    m_dataHexLabel = new QLabel(this);
    m_dataHexLabel->setGeometry(50,150,150,20);
    m_dataHexLabel->setText(FROMLOCAL("十六进制"));

    //创建 QRadioButton
    m_HexSelButtonGroup = new QButtonGroup(this);
   // m_ByteSelButtonGroup = new QButtonGroup(this);


    /*m_DwordButton = new QRadioButton(this);
    m_DwordButton->setGeometry(50,0,50,20);
    m_DwordButton->setText(FROMLOCAL("双字"));

    m_WordButton = new QRadioButton(this);
    m_WordButton->setGeometry(150,0,50,20);
    m_WordButton->setText(FROMLOCAL("单字"));

    m_ByteButton = new QRadioButton(this);
    m_ByteButton->setGeometry(100,0,50,20);
    m_ByteButton->setText(FROMLOCAL("字节"));*/

    m_dataFlaotButton = new QRadioButton(this);
    m_dataFlaotButton->setGeometry(50,20,50,20);
    m_dataFlaotButton->setText(FROMLOCAL("浮点"));
    m_dataFlaotButton->click();


    m_dataHexButton = new QRadioButton(this);
    m_dataHexButton->setGeometry(100,20,100,20);
    m_dataHexButton->setText(FROMLOCAL("十六进制"));


    m_dataHexAButton = new QRadioButton(this);
    m_dataHexAButton->setGeometry(250,20,100,20);
    m_dataHexAButton->setText(FROMLOCAL("正序"));
    m_dataHexAButton->hide();


    m_dataHexBButton = new QRadioButton(this);
    m_dataHexBButton->setGeometry(300,20,100,20);
    m_dataHexBButton->setText(FROMLOCAL("倒序"));
    m_dataHexBButton->hide();


    //创建控件 QlineEdit
    m_dataWriteEdit = new QLineEdit(this);
    m_dataWriteEdit->setGeometry(100,50,150,20);

    m_dataFloatEdit = new QLineEdit(this);
    m_dataFloatEdit->setGeometry(100,100,150,20);

    m_dataHexEdit = new QLineEdit(this);
    m_dataHexEdit->setGeometry(100,150,150,20);

    //创建控件 QPushButton
    m_converButton = new QPushButton(this);
    m_converButton->setGeometry(270,50,50,20);
    m_converButton->setText(FROMLOCAL("转换"));

  //  m_clearWriteButton = new QPushButton(this);
   // m_clearWriteButton->setGeometry(250,50,50,20);
  //  m_clearWriteButton->setText(FROMLOCAL("清空"));



    return true;
}

void Widget::InitUiFeature()
{
    //设置windows
    this->setWindowTitle(FROMLOCAL("转化工具"));
   // this->resize(500,300);
    this->setFixedSize(350,200);

    //设置 QRadioButton
    connect(m_dataFlaotButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    connect(m_dataHexButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    connect(m_dataHexAButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    connect(m_dataHexBButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    m_HexSelButtonGroup->addButton(m_dataHexAButton);
    m_HexSelButtonGroup->addButton(m_dataHexBButton);
   // m_ByteSelButtonGroup->addButton(m_DwordButton);
   // m_ByteSelButtonGroup->addButton(m_WordButton);
   // m_ByteSelButtonGroup->addButton(m_ByteButton);

   // m_DwordButton->click();


    //设置 QlineEdit
    m_dataFloatEdit->setReadOnly(true);
    m_dataHexEdit->setReadOnly(true);

    //设置 QPushButton
    connect(m_converButton,SIGNAL(released()),
            this,SLOT(FuncConvertion()));
}

void Widget::InitUiParam()
{
    m_iRadioId = 0;
    m_pConversion = new CConverTion();
    m_pRegExp = new QRegExpValidator(this);
    SetFloatMode();
}


void Widget::FuncConvertion()
{
    QString  str = m_dataWriteEdit->text();
    if( str.isEmpty())
    {
        m_dataFloatEdit->clear();
        m_dataHexEdit->clear();
        return;
    }
    char* ch;
    QByteArray ba = str.toLatin1();
    ch=ba.data();

    m_pConversion->Convertion(ch, m_iRadioId);

    m_dataFloatEdit->setText(QString::number(m_pConversion->m_fVal));
    m_dataHexEdit->setText(QString(m_pConversion->m_szHexBuf));
}

void Widget::radioChange()
{
    if(sender() == m_dataFlaotButton)
    {
        m_iRadioId = 0;
        m_dataHexAButton->hide();
        m_dataHexBButton->hide();
        m_dataWriteEdit->clear();
        SetFloatMode();

    }
    else if(sender() == m_dataHexButton)
    {
        m_iRadioId = 1;
        m_dataHexAButton->click();
        m_dataHexAButton->show();
        m_dataHexBButton->show();
        m_dataWriteEdit->clear();
        SetHexMode();
    }
    else if(sender() == m_dataHexAButton)
    {
        m_iRadioId = 2;
    }
    else if(sender() == m_dataHexBButton)
    {
        m_iRadioId = 3;
    }

}

void Widget::SetFloatMode()
{
    QRegExp rx("^-?[0-9]+\\.?\\d*$()|(^[+-]?([0-9]*\\.?[0-9]+|[0-9]+\\.?[0-9]*)([eE][+-]?[0-9]+)?$)");
    m_pRegExp->setRegExp(rx);
    m_dataWriteEdit->setValidator(m_pRegExp);

}

void Widget::SetHexMode()
{
    QRegExp rx("^([0-9a-fA-F]{1,2}\\ ?){4}$");
    m_pRegExp->setRegExp(rx);
    m_dataWriteEdit->setValidator(m_pRegExp);
}

