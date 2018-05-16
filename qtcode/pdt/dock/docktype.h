#ifndef DOCKTYPE_H
#define DOCKTYPE_H


#include	<QString>

const static QString DOCK_XML_PATH = QString( "./config/dock.xml" ); 

//connect func element
typedef struct _DOCK_CONFUNC_ELEMET
{
    int index; 
    QString name; 
    int wide; 
    QString type; 
    _DOCK_CONFUNC_ELEMET(  )
    {
        index = -1; 
        name = QString( "" ); 
        wide = 60; 
        type = QString( "" ); 
    }
}DOCK_CONFUNC_ELEMET;				/* ----------  end of struct DOCK_CONFUNC_ELEMET  ---------- */

//connect func
typedef struct _DOCK_CONFUNC
{
    int num; 
    QString name; 
    DOCK_CONFUNC_ELEMET *elemet;
    
    _DOCK_CONFUNC()
    {
        num = -1; 
        name = QString( "" ); 
        elemet = NULL; 
    }

}DOCK_CONFUNC;				/* ----------  end of struct DOCK_CONFUNC  ---------- */

//color name
typedef struct _DOCK_COLOR_ELEMET
{
    int index; 
    QString name; 
    QString funcname; 

    _DOCK_COLOR_ELEMET()
    {
        index = -1; 
        name = QString( "" );
        funcname = QString( "" ); 
    }
}DOCK_COLOR_ELEMET;				/* ----------  end of struct DOCK_COLOR_ELEMET  ---------- */

//color
typedef struct _DOCK_COLOR
{
    int num; 
    DOCK_COLOR_ELEMET *elemet; 

    _DOCK_COLOR()
    {
        num = -1; 
        elemet = NULL; 
    }
}DOCK_COLOR;				/* ----------  end of struct DOCK_COLOR  ---------- */

//view and edit
typedef struct _DOCK_EDIT
{
    QString name; 
    int readonly; 
    int maxrow; 

    _DOCK_EDIT()
    {
        name = QString( "" ); 
        readonly = 1; 
        maxrow = 1500; 
    }
}DOCK_EDIT;				/* ----------  end of struct DOCK_EDIT  ---------- */


//code elemet
typedef struct _DOCK_WIDGET_ELEMET
{
    int index; 
    QString name; 
    int funcindex; 
    _DOCK_WIDGET_ELEMET(  )
    {
        index = -1;
        name = QString( "" ); 
        funcindex = -1; 
    }
}DOCK_WIDGET_ELEMET;				/* ----------  end of struct DOCK_WIDGET_ELEMET  ---------- */


//code dock msgDock and log Dock
typedef struct _DOCK_WIDGET
{
    int num; 
    DOCK_WIDGET_ELEMET *elemet; 
    _DOCK_WIDGET( )
    {
        num = -1; 
        elemet = NULL; 
    }
}DOCK_WIDGET;				/* ----------  end of struct DOCK_WIDGET  ---------- */


//dockinfoelemet
typedef struct _DOCK_INFO_ELEMET
{
    int index; 
    QString name; 
    QString widget; 

    _DOCK_INFO_ELEMET()
    {
        index = -1;  
        name = QString( "" ); 
        widget = QString( "" );
    }
}DOCK_INFO_ELEMET;				/* ----------  end of struct DOCK_INFO_ELEMET  ---------- */


//dockinfo
typedef struct _DOCK_INFO
{
    int num; 
    DOCK_INFO_ELEMET *elemet; 
    _DOCK_INFO(  )
    {
        num = 0;
        elemet = NULL;
    }

}DOCK_INFO;				/* ----------  end of struct DOCK_INFO  ---------- */

//dock
typedef struct _DOCK
{
    DOCK_INFO info; 
    DOCK_WIDGET *widget; 
    DOCK_COLOR color;
    DOCK_CONFUNC confunc; 
    DOCK_EDIT edit; 
    
}DOCK;				/* ----------  end of struct DOCK  ---------- */


#endif // DOCKTYPE_H


