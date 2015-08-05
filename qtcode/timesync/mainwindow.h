#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimeEdit>
#include <QDateEdit>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    //初始化界面
    void InitUi( );
private:
    //定义时间控件指针
    QTimeEdit *m_timeEditTime;
    //定义日期时间指针
    QDateEdit *m_dateEditDate;
    //定义定时期指针
    QTimer *m_timer;
    //定义时间指针
    QTime *m_time;
    //定义日期指针
    QDate *m_date;

private slots:
    //时间变化的槽
    void TimeUpdate( void );
    //设置当前时间
    void SetCurrenTime( QTime t);
    //设置当前日期
    void SetCurrenDate( QDate d);
};

#endif // MAINWINDOW_H
