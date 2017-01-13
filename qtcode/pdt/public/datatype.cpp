
#include	"datatype.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  StrTopChar
 *  Description:  
 * =====================================================================================
 */
char * StrTopChar ( QString str )
{
    QByteArray ba =str.toLatin1();

    return ba.data();
}		/* -----  end of function StrTopChar  ----- */
