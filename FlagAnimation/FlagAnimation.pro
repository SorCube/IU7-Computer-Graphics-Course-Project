QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canvas.cpp \
    drawer.cpp \
    facade/facade.cpp \
    filemanager/filemanager.cpp \
    flag/flag.cpp \
    main.cpp \
    mainwindow.cpp \
    managers/drawmanager.cpp \
    model/mathvector.cpp \
    model/model.cpp \
    model/triangle.cpp \
    model/vertex.cpp \
    scene/camera.cpp \
    scene/scene.cpp \
    workers/modelbuilder.cpp \
    workers/modelcreator.cpp \
    workers/modeluploader.cpp \
    workers/objecttransformator.cpp

HEADERS += \
    canvas.h \
    drawer.h \
    exceptions/baseexception.h \
    exceptions/buildexception.h \
    exceptions/drawexception.h \
    exceptions/objectexception.h \
    exceptions/transformexception.h \
    exceptions/uploadexception.h \
    facade/facade.h \
    filemanager/filemanager.h \
    flag/flag.h \
    mainwindow.h \
    managers/drawmanager.h \
    managers/objectmanager.h \
    managers/uploadmanager.h \
    model/mathvector.h \
    model/model.h \
    model/object.h \
    model/triangle.h \
    model/vertex.h \
    scene/camera.h \
    scene/scene.h \
    transformation/transformation.h \
    workers/modelbuilder.h \
    workers/modelcreator.h \
    workers/modeluploader.h \
    workers/objecttransformator.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
