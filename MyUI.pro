#-------------------------------------------------
#
# Project created by QtCreator 2017-04-13T14:55:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += svg

TARGET = MyUI
TEMPLATE = app


SOURCES += main.cpp\
    shared/movable.cpp \
    mainwidget.cpp \
    shared/FramelessHelper.cpp \
    shared/TitleBar.cpp \
    shadowdialog/simpledialog.cpp \
    shadowdialog/customdialog.cpp \
    shared/QCustomLineEdit.cpp \
    shadowdialog/stackeddialog.cpp \
    shadowdialog/anothershadowwidget.cpp \
    diffsize/leftbar.cpp \
    diffsize/NumberButton.cpp \
    shared/imagefactory.cpp \
    shared/ImageOp.cpp

HEADERS  += \
    shared/movable.h \
    mainwidget.h \
    shared/FramelessHelper.h \
    shared/FramelessHelper_p.h \
    shared/TitleBar.h \
    shadowdialog/simpledialog.h \
    shadowdialog/customdialog.h \
    shared/QCustomLineEdit.h \
    shadowdialog/stackeddialog.h \
    shadowdialog/anothershadowwidget.h \
    diffsize/leftbar.h \
    diffsize/NumberButton.h \
    shared/imagefactory.h \
    shared/ImageOp.h

FORMS    += \
    shadowdialog/simpledialog.ui \
    shadowdialog/stackeddialog.ui \
    shadowdialog/anothershadowwidget.ui

RESOURCES += \
    shared/shared.qrc \
    shadowdialog/shadowdialog.qrc \
    diffsize/diffsize.qrc

DISTFILES +=

INCLUDEPATH += $$PWD/
INCLUDEPATH += $$PWD/shared/

