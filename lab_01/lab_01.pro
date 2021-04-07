QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connections.cpp \
    drawing.cpp \
    errors.cpp \
    figure.cpp \
    file_proc.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    operations.cpp \
    point.cpp \
    task_manager.cpp

HEADERS += \
    connections.h \
    drawing.h \
    errors.h \
    figure.h \
    file_proc.h \
    graph.h \
    mainwindow.h \
    operations.h \
    point.h \
    task_manager.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
