#include "cconvertion.h"

#include	<stdio.h>
//#include	<stdlib.h>
#include	<string.h>


CConverTion::CConverTion()
{
    m_fVal = 0.0;
    memset(m_szHexBuf, 0, sizeof(m_szHexBuf));
}

CConverTion::~CConverTion()
{

}

bool CConverTion::Convertion(char *szLineBuf, int szDataType)
{
#ifdef  DebugMod
qDebug() << "Convertion"<<szDataType;
#endif

    unsigned char szTmpBuf[4];
    unsigned char szTmpBuf1[4];
    unsigned char *p;

    m_fVal = 0.0;
    memset(m_szHexBuf, 0, sizeof(m_szHexBuf));

    switch(szDataType)
    {
    case 0://float
        sscanf( szLineBuf, "%f",  &m_fVal );
        p = (unsigned char *)&m_fVal;

        sprintf_s(m_szHexBuf, "%02x %02x %02x %02x",
                  *p, *(p+1), *(p+2), *(p+3));
        break;
    case 1://byte
    case 2://byte ->
        sscanf( szLineBuf, "%2x %2x %2x %2x",
                (unsigned int *)&szTmpBuf[0], (unsigned int *)&szTmpBuf[1], (unsigned int *)&szTmpBuf[2], (unsigned int *)&szTmpBuf[3]);
        memcpy( &m_fVal, szTmpBuf, 4 );
        sprintf(m_szHexBuf, "%02x %02x %02x %02x",
                szTmpBuf[0], szTmpBuf[1], szTmpBuf[2], szTmpBuf[3]);
        break;
    case 3://byte <-
        sscanf( szLineBuf, "%2x %2x %2x %2x",
                (unsigned int *)&szTmpBuf1[0], (unsigned int *)&szTmpBuf1[1], (unsigned int *)&szTmpBuf1[2], (unsigned int *)&szTmpBuf1[3]);

                szTmpBuf[3]  = szTmpBuf1[0];
                szTmpBuf[2]  = szTmpBuf1[1];
                szTmpBuf[1]  = szTmpBuf1[2];
                szTmpBuf[0]  = szTmpBuf1[3];

        memcpy( &m_fVal, szTmpBuf, 4 );
        sprintf(m_szHexBuf, "%02x %02x %02x %02x",
                szTmpBuf[0], szTmpBuf[1], szTmpBuf[2], szTmpBuf[3]);
        break;
    default:

        break;
    }

#ifdef  DebugMod
  qDebug() << m_fVal << m_szHexBuf << endl;
#endif



    return true;
}
