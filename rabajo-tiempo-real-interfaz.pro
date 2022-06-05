QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    conversor.cpp \
    fdt.cpp \
    funciones_hilos.cpp \
    main.cpp \
    mainwindow.cpp \
    planta.cpp \
    qcustomplot.cpp \
    regulador.cpp \
    sensor.cpp \
    variablescompartidas.cpp

HEADERS += \
    config.h \
    conversor.h \
    fdt.h \
    funciones_hilos.h \
    mainwindow.h \
    planta.h \
    qcustomplot.h \
    regulador.h \
    sensor.h \
    variablescompartidas.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
