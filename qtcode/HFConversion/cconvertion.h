#ifndef CCONVERTION_H
#define CCONVERTION_H

//#define DebugMod

#ifdef  DebugMod
    #include <QDebug>
#endif

class CConverTion
{
public:
    CConverTion();
    ~CConverTion();

public:
    bool Convertion(char *szLineBuf, int szDataType);

public:
    float m_fVal;
    char m_szHexBuf[256];


};

#endif // CCONVERTION_H
