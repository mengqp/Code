#ifndef CXML_H
#define CXML_H

#include <QDir>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QDomDocument>
#include <QDebug>


class CXml
{
public:
    CXml();
    ~CXml();

public:
    bool OpenXml( QString strXmlFilePath );
    void CloseXml( );

    void GetRoot( ) ;
    QDomNode GetNode( QString strName);
    QString GetNodeInfo( QDomNode n, QString strName);
    QDomNode GetFirstElemet( QDomNode n );
    void ElemetNext( QDomNode &e);
    QString GetNodeElemetInfo( QDomNode n, QString strName);

    //修改xml node 的值
    bool SetNode( QString strNode,  QString strNodeName,  QString strNodeAttr ); 
    bool SetNode( QString strNode,  QString strNodeName,  int iNodeAttr ); 
    //修改xml node element 的值
    bool SetNodeElemet(QString strNode, 
            int iIndex ,  
            QString strNodeName, 
            QString strNodeAttr ); 
    bool SetNodeElemet( QString strNode, 
            int iIndex ,  
            QString strNodeName,  
            int iNodeAttr );
    


public:
    QFile m_XmlFile;
    QDomElement m_Root ;
    QDomDocument m_doc;

    QString m_FilePath;
};

#endif // CXML_H
