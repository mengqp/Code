#include "cxml.h"
#include	"errormsg.h"

CXml::CXml()
{

}

CXml::~CXml()
{

}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CXml
 *      Method:  OpenXml
 * Description:  打开xml
 *	 Input:  strXmlFilePath:路径
 *	Return:
 *--------------------------------------------------------------------------------------
 */
bool CXml::OpenXml ( const QString strXmlFilePath )
{
    if( strXmlFilePath.isEmpty() )
    {
        printTips( "CXml::OpenXml", "StrXmlFilePath is empty");
        return false;
    }

    m_FilePath = strXmlFilePath;

  /*  QStringList list = strXmlFilePath.split("/");

    m_XmlFile.setFileName( list.last());
    int count = list.size();
    if( count > 1)
    {
        QString path;
        for( int i=0; i<count-1;i++)
        {
            path += list.at(i);
            path += "/";
        }
        QDir::setCurrent( path );
    }*/

    m_XmlFile.setFileName( strXmlFilePath );

    if (!m_XmlFile.open(QIODevice::ReadWrite))
    {
       printTips( "CXml::OpenXml", "m_XmlFile open error");
        return false;
    }

    return true;
}		/* -----  end of method CXml::OpenXml  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CXml
 *      Method:  CloseXml
 * Description:  关闭xml文件	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
void CXml::CloseXml (  )
{
    if( m_XmlFile.isOpen())
    {
        m_XmlFile.close();
    }

}		/* -----  end of method CXml::CloseXml  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CXml
 *      Method:  GetRoot
 * Description: 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
void CXml::GetRoot (  )
{
    if (!m_doc.setContent(&m_XmlFile))
    {
       printTips( "CXml::GetRoot", "setContent error");
        CloseXml( );
        return;
    }

    m_Root = m_doc.documentElement();
}		/* -----  end of method CXml::GetRoot  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CXml
 *      Method:  GetNode
 * Description: 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
QDomNode CXml::GetNode ( QString strName )
{
    QDomNode n = m_Root.firstChild();

    while( !n.isNull())
    {
        QString strNoteName = n.nodeName();
        if( strNoteName == strName)
        {
            return n;
        }

        n = n.nextSibling();
    }
    
    n.clear();
    return n;
}		/* -----  end of method CXml::GetNode  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CXml
 *      Method:  GetNodeInfo
 * Description: 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
QString CXml::GetNodeInfo ( QDomNode n,  QString strName )
{
    QDomElement e = n.toElement();
    return e.attribute(strName);
}		/* -----  end of method CXml::GetNodeInfo  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CXml
 *      Method:  GetFirstElemet
 * Description: 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
QDomNode CXml::GetFirstElemet ( QDomNode n )
{
    QDomNode e = n.firstChild(  );
    return e;
}		/* -----  end of method CXml::GetFirstElemet  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  CXml
 *      Method:  ElemetNext
 * Description: 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
void CXml::ElemetNext ( QDomNode &e )
{
    e = e.nextSibling();
}		/* -----  end of method CXml::ElemetNext  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CXml
 *      Method:  GetNodeElemetInfo
 * Description: 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
QString CXml::GetNodeElemetInfo ( QDomNode n,  QString strName )
{
    QDomElement e = n.toElement();
    return e.attribute(( strName));
}		/* -----  end of method CXml::GetNodeElemetInfo  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CXml
 *      Method:  SetNode
 * Description:  设置节点属性 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CXml::SetNode ( QString strNode,  QString strNodeName,  QString strNodeAttr )
{
    QDomNode node = GetNode( strNode );
    if( node.isNull(  ) )
    {
        return false;
    }

    QString str = GetNodeInfo(node,strNodeName);
    if( !str.isEmpty() && (0 != str.compare(strNodeAttr)))
    {
        QDomElement e = node.toElement( );
        e.setAttribute(strNodeName, strNodeAttr);

        QFile file( m_FilePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return false;
        }
        QTextStream out(&file);
        m_doc.save(out,4);
        return true; 

    }

    return false;
}		/* -----  end of method CXml::SetNode  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CXml
 *      Method:  SetNode
 * Description: 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CXml::SetNode ( QString strNode,  QString strNodeName,  int iNodeAttr )
{
    bool ok; 
    QDomNode node = GetNode( strNode );
    if( node.isNull(  ) )
    {
        return false;
    }

    int  iAttr = GetNodeInfo(node,strNodeName).toInt( &ok,  10 );
    if( iAttr != iNodeAttr )
    {
        QDomElement e = node.toElement( );
        e.setAttribute(strNodeName, iNodeAttr);

        QFile file( m_FilePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return false;
        }
        QTextStream out(&file);
        m_doc.save(out,4);
        return true; 

    }

    return false;
}		/* -----  end of method CXml::SetNode  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CXml
 *      Method:  SetNodeElemet
 * Description:  设置节点elemet值	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CXml::SetNodeElemet ( QString strNode, 
        int  iIndex, 
        QString strName, 
        QString strNodeAttr)
{
    if( iIndex <  0 )
    {
        return false; 
    }

    QDomNode node = GetNode( strNode );
    if( node.isNull(  ) )
    {
        return false;
    }

    QDomNode elenode = GetFirstElemet( node ); 
    int i; 
    for( i=0; !elenode.isNull(); i++ )
    {
        if( iIndex != i )
        {
            ElemetNext( elenode ); 
            continue; 
        }

        QString str = GetNodeElemetInfo(elenode,strName);
        if( !str.isEmpty() && (0 != str.compare(strNodeAttr)))
        {
            QDomElement e = elenode.toElement( );
            e.setAttribute(strName, strNodeAttr);

            QFile file( m_FilePath);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                return false;
            }
            QTextStream out(&file);
            m_doc.save(out,4);
            return true; 

        }
    }

    return false;
}		/* -----  end of method CXml::SetNodeElemet  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  CXml
 *      Method:  SetNodeElemet
 * Description: 	
 *		 Input:
 *		Return:
 *--------------------------------------------------------------------------------------
 */
bool CXml::SetNodeElemet ( QString strNode, 
        int  iIndex, 
        QString strName, 
        int iNodeAttr )
{
    bool ok; 
    if( iIndex <  0 )
    {
        return false; 
    }

    QDomNode node = GetNode( strNode );
    if( node.isNull(  ) )
    {
        return false;
    }

    QDomNode elenode = GetFirstElemet( node ); 
    int i; 
    for( i=0; !elenode.isNull(); i++ )
    {
        if( iIndex != i )
        {
            ElemetNext( elenode ); 
            continue; 
        }

        int iAttr = GetNodeElemetInfo(elenode,strName).toInt( &ok, 10);
        if( iAttr != iNodeAttr)
        {
            QDomElement e = elenode.toElement( );
            e.setAttribute(strName, iNodeAttr);

            QFile file( m_FilePath);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                return false;
            }

            QTextStream out(&file);
            m_doc.save(out,4);
            return true; 

        }
    }

    return false;
}		/* -----  end of method CXml::SetNodeElemet  ----- */

