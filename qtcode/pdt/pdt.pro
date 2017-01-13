#-------------------------------------------------
#
# Project created by QtCreator 2015-10-30T08:58:11
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../../pdt/release/pdt
TEMPLATE = app


SOURCES += main.cpp\
        pdtwindow.cpp \
    public/cxml.cpp \
    public/errormsg.cpp \
    public/datatype.cpp \
    project/cprjnew.cpp \
    project/cprjopen.cpp \
    dock/cdock.cpp \
    tab/ctab.cpp \
    comm/ccomm.cpp

HEADERS  += pdtwindow.h \
    public/cxml.h \
    public/errormsg.h \
    public/datatype.h \
    project/cprjnew.h \
    project/cprjopen.h \
    dock/cdock.h \
    tab/ctab.h \
    dock/docktype.h \
    comm/ccomm.h
