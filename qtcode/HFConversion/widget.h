#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>

#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QRegExpValidator>

#include	"cconvertion.h"

#define FROMLOCAL(a) QString::fromUtf8(a)


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();


private:
    bool InitUi(void);
    void InitUiFeature();
    void InitUiParam();

    void SetFloatMode( void );
    void SetHexMode( void );


private slots:
    void FuncConvertion();
    void radioChange();

private:
    QButtonGroup *m_HexSelButtonGroup;
    QButtonGroup *m_ByteSelButtonGroup;


    QRadioButton *m_ByteButton;
    QRadioButton *m_WordButton;
    QRadioButton *m_DwordButton;

    QRadioButton *m_dataFlaotButton;
    QRadioButton *m_dataHexButton;


    QRadioButton *m_dataHexAButton;
    QRadioButton *m_dataHexBButton;


    QLabel *m_dataFloatLabel;
    QLabel *m_dataHexLabel;

    QLineEdit  *m_dataWriteEdit;
    QLineEdit  *m_dataFloatEdit;
    QLineEdit  *m_dataHexEdit;

    QRegExpValidator *m_pRegExp;

    QPushButton *m_converButton;
   // QPushButton *m_clearWriteButton;

    CConverTion *m_pConversion; 

    int m_iRadioId;

};

#endif // WIDGET_H
