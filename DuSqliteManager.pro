#-------------------------------------------------
#
# Author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
#
# Project created by QtCreator 2015-01-02T19:41:44
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DuSqliteManager
TEMPLATE = app

SOURCES += main.cpp\
    DuSqliteManagerSettings.cpp \
    DuSqliteManagerNewTableDialog.cpp \
    DuSqliteManagerPreferencesDialog.cpp \
    DuSqliteManagerTreeWidget.cpp \
    DuSqliteManagerFindDialog.cpp \
    DuSqliteManagerFindForm.cpp \
    DuSqliteManagerFindReplaceDialog.cpp \
    DuSqliteManagerFindReplaceForm.cpp \
    DuSqliteManagerMainWindow.cpp \
    DuSqliteManagerEditDataDialog.cpp

HEADERS  += \
    DuSqliteManagerSettings.h \
    DuSqliteManagerDefines.h \
    DuSqliteManagerNewTableDialog.h \
    DuSqliteManagerPreferencesDialog.h \
    DuSqliteManagerTreeWidget.h \
    DuSqliteManagerFindDialog.h \
    DuSqliteManagerFindForm.h \
    DuSqliteManagerFindReplaceDialog.h \
    DuSqliteManagerFindReplaceForm.h \
    DuSqliteManagerMainWindow.h \
    DuSqliteManagerEditDataDialog.h

FORMS    += \
    DuSqliteManagerNewTableDialog.ui \
    DuSqliteManagerPreferencesDialog.ui \
    DuSqliteManagerFindReplaceDialog.ui \
    DuSqliteManagerFindReplaceForm.ui \
    DuSqliteManagerMainWindow.ui \
    DuSqliteManagerEditDataDialog.ui

RESOURCES += \
    res.qrc

QMAKE_CXXFLAGS += -std=gnu++14
