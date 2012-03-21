#-------------------------------------------------
#
# Project created by QtCreator 2012-03-21T12:21:58
#
#-------------------------------------------------

QT       += core gui xml opengl

TARGET = XDFLViewer
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    xdflview.cpp \
    camera.cpp \
    renderablexdflobject.cpp \
    renderablexdflpath.cpp \
    renderablexdflvoxel.cpp

HEADERS  += mainwindow.h \
    xdflview.h \
    camera.h \
    renderablexdflobject.h \
    renderablexdflpath.h \
    renderablexdflvoxel.h

INCLUDEPATH += Eigen/
FORMS    += mainwindow.ui










