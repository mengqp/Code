#ifndef ERRORMSG_H
#define ERRORMSG_H

#include	<QString>
#include	<QMessageBox>
#include	<QDebug>

extern "C"
{
void printTips ( QString strFuncName,  QString strTip );
void printLogs ( QString strFuncName,  QString strTip );
}


#endif // ERRORMSG_H
