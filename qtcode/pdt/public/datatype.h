#ifndef DATATYPE_H
#define DATATYPE_H

using namespace std;
#define FROMLOCAL(a) QString::fromUtf8(a)

#include	<QString>

#define	    PORT_SERIAL     1			/*  */

//menu elemet
typedef struct _PDT_MENU_ELEMET
{
    int index; 
    QString name; 
    QString code; 
    _PDT_MENU_ELEMET(  )
    {
        index = -1; 
        name = QString( "" ); 
        code = QString( "" ); 
    }
}PDT_MENU_ELEMET;				/* ----------  end of struct PDT_MENU_ELEMET  ---------- */

//menu
typedef struct _PDT_MENU
{
    int num; 
    QString name; 
    PDT_MENU_ELEMET *elemet; 

    _PDT_MENU(  )
    {
        num = 0; 
        name = QString( "" ); 
        elemet = NULL; 
    }


}PDT_MENU;				/* ----------  end of struct PDT_MENU  ---------- */


//tool elemet
typedef struct _PDT_TOOL_ELEMET
{
    int index; 
    int menuindex; 
    int elemetindex; 
    _PDT_TOOL_ELEMET(  )
    {
        index = -1; 
        menuindex = -1;
        elemetindex = -1; 
    }

}PDT_TOOL_ELEMET;				/* ----------  end of struct PDT_TOOL_ELEMET  ---------- */

//tool bar
typedef struct _PDT_TOOL
{
    int num ; 
    QString name; 
    int menuindex;
    PDT_TOOL_ELEMET *elemet; 
    _PDT_TOOL(  )
    {
        num = 0; 
        name = QString( "" ); 
        menuindex=-1;
        elemet = NULL; 
    }
    
}PDT_TOOL;				/* ----------  end of struct PDT_TOOL  ---------- */

//
typedef struct _PDT_ACTION_ELEMET 
{
    int index; 
    QString name; 
    QString pic; 
    QString shortcut; 
    QString tips; 
    _PDT_ACTION_ELEMET(  )
    {
        index = -1; 
        name = QString( "" ); 
        pic = QString( "" ); 
        shortcut = QString( "" ); 
        tips = QString( "" ); 
    }

}PDT_ACTION_ELEMET;				/* ----------  end of struct PDT_ACTION_ELEMET  ---------- */
//acttion
typedef struct _PDT_ACTION 
{
    int num; 
    PDT_ACTION_ELEMET *elemet; 
    _PDT_ACTION(  )
    {
        num = 0; 
        elemet = NULL; 
    }

}PDT_ACTION;				/* ----------  end of struct PDT_ACTION  ---------- */


//confunc elemet
typedef struct _PDT_CONFUNC_ELEMET
{
    int index; 
    QString name; 
    int menuindex; 
    int elemetindex; 
    _PDT_CONFUNC_ELEMET()
    {
        index = -1; 
        name = QString( "" ); 
        menuindex = -1; 
        elemetindex = -1; 
    }
}PDT_CONFUNC_ELEMET;				/* ----------  end of struct _PDT_CONFUNC_ELEMET  ---------- */

//confunc
typedef struct _PDT_CONFUNC
{
    int num; 
    QString name; 
    PDT_CONFUNC_ELEMET *elemet; 
    
    _PDT_CONFUNC(  )
    {
        num = 0; 
        name = QString( "" ); 
    }


}PDT_CONFUNC;				/* ----------  end of struct _PDT_CONFUNC  ---------- */



//pdt
typedef struct _PDT 
{
    PDT_MENU menu; 
    PDT_TOOL tool; 
    PDT_ACTION *action; 
    PDT_CONFUNC confunc; 
    _PDT(  )
    {
        action = NULL; 
    }

}PDT;				/* ----------  end of struct pdt  ---------- */

//
typedef struct 
{
    unsigned int index; 
    char name[64]; 
    float value; 
    char unit[32]; 
    unsigned int soucevalue; 
    float scale; 
    unsigned int cmdline; 
    unsigned int offsetbyte; 
    unsigned int datalen;
    unsigned int dataformat;
    unsigned int symbol; 
    unsigned int shieldcode;

}DATATYPE_YC;				/* ----------  end of struct DATATYPE_YC  ---------- */


//
typedef struct 
{
    char serial[16]; 
    unsigned int baud; 
    unsigned int datebyte; 
    unsigned int checkbyte; 
    unsigned int stopbyte; 

}DATATYPE_PORT_SERIAL;				/* ----------  end of struct DATATYPE_PORT_SERIAL  ---------- */


//
typedef struct 
{
    unsigned int type; 
    DATATYPE_PORT_SERIAL serial; 
    unsigned int inteval; 
}DATATYPE_PORT;				/* ----------  end of struct DATATYPE_PORT  ---------- */


//
typedef struct 
{
    unsigned int index; 
    unsigned int funccode; 
    unsigned int registeraddr; 
    unsigned int registernum; 
    char bak[256]; 
}DATATYPE_TEMPLATE_CMD;				/* ----------  end of struct DATATYPE_TEMPLATE_CMD  ---------- */

//
typedef struct 
{
    char name[128]; 
    unsigned int addr; 
    unsigned int yxnum; 
    unsigned int ycnum; 
    unsigned int ymnum; 
    unsigned int yknum; 
    unsigned int dznum; 
    unsigned int cmdnum; 
    DATATYPE_TEMPLATE_CMD cmd[128]; 
}DATATYPE_TEMPLATE;				/* ----------  end of struct DATATYPE_TEMPLATE  ---------- */


//
typedef struct 
{
    DATATYPE_PORT port; 
    DATATYPE_TEMPLATE tmplate; 
    DATATYPE_YC yc[1024]; 

}DATATYPE_UNIT;				/* ----------  end of struct DATATYPE_UNIT  ---------- */



extern "C"
{
char * StrTopChar ( QString str );
}


#endif // DATATYPE_H

