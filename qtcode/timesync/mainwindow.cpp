#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化值
    m_timeEditTime = NULL;
    m_dateEditDate = NULL;
    m_timer = NULL;
    m_time = NULL;
    m_date = NULL;

    //初始化界面
    InitUi( );
}

MainWindow::~MainWindow()
{
    //删除时间指针
    if( NULL != m_timeEditTime)
    {
        delete m_timeEditTime;
        m_timeEditTime = NULL;
    }
    //删除日期指针
    if( NULL != m_dateEditDate )
    {
        delete m_dateEditDate;
        m_dateEditDate = NULL;
    }

    //删除定时器指针
    if( NULL != m_timer)
    {
        delete m_timer;
        m_timer = NULL;
    }

    //删除时间
    if( NULL != m_time)
    {
        delete m_time;
        m_time = NULL;
    }
    //删除日期
    if( NULL != m_date )
    {
        delete m_date;
        m_date = NULL;
    }

    delete ui;
}

/*初始化界面*/
void MainWindow::InitUi()
{
    /* 时间格式的基本定义 */
    m_timeEditTime = new QTimeEdit( this );
    // 位置
    m_timeEditTime->setGeometry(100, 50, 200,30);
    // 显示格式
    m_timeEditTime->setDisplayFormat( "HH:mm:ss");
    // 创建设置时间的链接
    connect( m_timeEditTime,
             SIGNAL( timeChanged(QTime)),
             this,
             SLOT( SetCurrenTime(QTime)));


    /* 日期格试的基本定义 */
    m_dateEditDate = new QDateEdit( this );
    // 位置
    m_dateEditDate->setGeometry( 100, 120, 200,30);
    // 显示格式
    m_dateEditDate->setDisplayFormat("yyyy-MM-dd");
    // 创建设置日期的链接
    connect( m_dateEditDate,
             SIGNAL(dateChanged(QDate)),
             this,
             SLOT( SetCurrenDate(QDate)));

    /* 定时器的定义 */
    m_timer = new QTimer( this );
    // 创建时间更新的信号和槽
    connect(m_timer,
            SIGNAL(timeout()),
            this,
            SLOT( TimeUpdate()) );
    // 开始计时
    m_timer->start( 1000 );

    /* 定义时间 */
    m_time = new QTime( QTime::currentTime().hour(),
                        QTime::currentTime().minute(),
                        QTime::currentTime().second());

    /* 定义日期 */
    m_date = new QDate( QDate::currentDate().year(),
                        QDate::currentDate().month(),
                        QDate::currentDate().day());

    m_dateEditDate->setDate( *m_date );
}

//槽 时间更新
void MainWindow::TimeUpdate( void )
{
   // 显示本地时间
   //m_timeEditTime->setTime( QTime::currentTime());
   //m_dateEditDate->setDate( QDate::currentDate());


   // 显示设置时间
   QTime newTime = m_time->addMSecs(1000);
   m_timeEditTime->setTime( newTime );

   if( 23 == m_time->hour()
           && 59 == m_time->minute()
           && 59 == m_time->second())
   {
       QDate newDate = m_date->addDays( 1 );
       m_dateEditDate->setDate( newDate );
   }
}

//槽 设置当前时间
void MainWindow::SetCurrenTime( QTime t )
{
   m_time->setHMS( t.hour(),
                   t.minute(),
                   t.second());
}

//槽 设置当前时间
void MainWindow::SetCurrenDate( QDate d )
{
    m_date->setDate( d.year(),
                     d.month(),
                     d.day());
}

