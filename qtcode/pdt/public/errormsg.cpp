#include "errormsg.h"
#include "datatype.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  printTips
 *  Description:  
 * =====================================================================================
 */
void printTips ( QString strFuncName,  QString strTip )
{
    QString strTips = "[" + strFuncName + "]" + ":" + strTip;
    QMessageBox::about(NULL, FROMLOCAL("提示"), strTips);
}		/* -----  end of function printTips  ----- */

void printLogs( QString strFuncName,  QString strLogs )
{
    qDebug(  )  <<  strFuncName  <<  strLogs;  
}
