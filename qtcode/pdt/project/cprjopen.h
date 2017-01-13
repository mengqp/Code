#ifndef CPRJOPEN_H
#define CPRJOPEN_H

#include <QMainWindow>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QFileDialog>

#include "../public/datatype.h"

class CPrjOpen : public QDialog
{
    Q_OBJECT
public:
    explicit CPrjOpen(QMainWindow *parent = 0);
    ~CPrjOpen();
public:

private:
    void InitUI(void);
    //设置信号和槽功能
    void SetConnectFunc(void);
    //设置基本属性
    void SetAttri();
public:
    QLabel *m_labelPrjPath;

    QLineEdit *m_linePath;

    QPushButton *m_buttonPath;
    QPushButton *m_buttonOk;
    QPushButton *m_buttonCancel;

    //QDialog *m_dialogPrjOpen;
private:
    //定义主窗口
    QMainWindow *m_mainWindow;

private slots:
    //保存退出Dialog
    void SaveCloseDialog(void);
    //点击浏览->获取路径
    void GetOpenPrj(void);
    //设置工程参数
    bool SetPrjParam( void );
};

#endif // CPRJOPEN_H
